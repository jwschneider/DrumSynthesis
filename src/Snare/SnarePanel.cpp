#include "Snare.hpp"
#include "../common/Components.hpp"

using namespace snare;

class ModMatrixWidget : public TransparentWidget {
    public:
    ModMatrixWidget()
    {
        font = APP->window->loadFont(asset::plugin(pluginInstance, "res/clacon.ttf"));
    }
    void setEngine(SnareEngine *engine)
    {
        this->engine = engine;
    }
    void draw(const DrawArgs &args) override
    {
        if (!engine)
        {
            return;
        }
        nvgFontSize(args.vg, 20);
        nvgFontFaceId(args.vg, font->handle);
        std::string to_display = "x";
        NVGcolor textcolor = nvgRGB(0x16, 0xb2, 0x16);
        nvgFillColor(args.vg, textcolor);
        for (int i = 0; i < Snare::NUM_PARAMS; i++)
        {
            if (engine->_modMatrix[i][4] > 0)
                for (int j = 0; j < 4; j++)
                {
                    if (engine->_modMatrix[i][j])
                    {
                        Vec textPos = Vec(i * box.size.x / 4, j * box.size.y / Snare::NUM_PARAMS);
                        nvgText(args.vg, textPos.x, textPos.y, to_display.c_str(), NULL);
                    }
                }
        }
    }
    void onButton(const event::Button& e) override
    {
        if (e.button == GLFW_MOUSE_BUTTON_LEFT)
        {
            // calculate which i, j in panel, but set the bits in the array in engine
            int i = e.pos.x / 4;
            int j = e.pos.y / Snare::NUM_PARAMS;
            int val = engine->_modMatrix[i][j];
            if (val)
            {
                engine->_modMatrix[i][4]--;
                engine->_modMatrix[i][j] = 0;
            }
            else
            {
                engine->_modMatrix[i][4]++;
                engine->_modMatrix[i][j] = 1;
            }
            e.consume(this);
        }
    }
    private:
    int count = 0;
    std::shared_ptr<Font> font;
    SnareEngine *engine;
};

snare::SnarePanel::SnarePanel(Snare *module)
{    	
    setModule(module);
    setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/Snare.svg")));

    addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
    addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
    addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
    addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

    addParam(createParamCentered<KnobSmallDirectional>(mm2px(Vec(10.387, 11.764)), module, Snare::BASEFQ_PARAM));
    addParam(createParamCentered<KnobSmallDirectional>(mm2px(Vec(20.335, 11.764)), module, Snare::BASEDECAY_PARAM));
    addParam(createParamCentered<KnobSmallDirectional>(mm2px(Vec(30.283, 11.764)), module, Snare::BASEAMP_PARAM));
    addParam(createParamCentered<KnobSmallerDirectional>(mm2px(Vec(39.526, 11.87)), module, Snare::MOD0_PARAM));
    addParam(createParamCentered<KnobSmallerDirectional>(mm2px(Vec(45.48, 11.87)), module, Snare::MOD1_PARAM));
    addParam(createParamCentered<KnobSmallerDirectional>(mm2px(Vec(51.434, 11.87)), module, Snare::MOD2_PARAM));
    addParam(createParamCentered<KnobSmallerDirectional>(mm2px(Vec(57.388, 11.87)), module, Snare::MOD3_PARAM));
    addParam(createParamCentered<KnobSmallDirectional>(mm2px(Vec(10.387, 26.58)), module, Snare::HARMONIC1_PARAM));
    addParam(createParamCentered<KnobSmallDirectional>(mm2px(Vec(20.335, 26.58)), module, Snare::HARMONIC2_PARAM));
    addParam(createParamCentered<KnobSmallDirectional>(mm2px(Vec(30.283, 26.58)), module, Snare::HARMONICSPACING_PARAM));
    addParam(createParamCentered<KnobSmallDirectional>(mm2px(Vec(15.348, 39.611)), module, Snare::HARMONICDECAY_PARAM));
    addParam(createParamCentered<KnobSmallDirectional>(mm2px(Vec(25.296, 39.611)), module, Snare::HARMONICAMP_PARAM));
    addParam(createParamCentered<KnobSmallDirectional>(mm2px(Vec(10.387, 54.392)), module, Snare::FMTONE_PARAM));
    addParam(createParamCentered<KnobSmallDirectional>(mm2px(Vec(20.335, 54.392)), module, Snare::FMCHARACTER_PARAM));
    addParam(createParamCentered<KnobSmallDirectional>(mm2px(Vec(30.283, 54.392)), module, Snare::FMDEPTH_PARAM));
    addParam(createParamCentered<KnobSmallDirectional>(mm2px(Vec(15.348, 67.423)), module, Snare::FMFEEDBACK_PARAM));
    addParam(createParamCentered<KnobSmallDirectional>(mm2px(Vec(25.296, 67.423)), module, Snare::FMAMP_PARAM));
    addParam(createParamCentered<SnapKnobSmallDirectional>(mm2px(Vec(10.387, 82.096)), module, Snare::NOISECOLOR_PARAM));
    addParam(createParamCentered<KnobSmallDirectional>(mm2px(Vec(20.335, 82.096)), module, Snare::RINGMODULATION_PARAM));
    addParam(createParamCentered<KnobSmallDirectional>(mm2px(Vec(30.283, 82.096)), module, Snare::NOISEAMP_PARAM));
    addParam(createParamCentered<KnobSmallDirectional>(mm2px(Vec(10.387, 96.913)), module, Snare::VELOCITY_PARAM));
    addParam(createParamCentered<KnobSmallDirectional>(mm2px(Vec(20.335, 96.913)), module, Snare::SNAREDECAY_PARAM));
    addParam(createParamCentered<KnobSmallDirectional>(mm2px(Vec(30.283, 96.913)), module, Snare::SNAREAMP_PARAM));
    addParam(createParam<DSSwitch>(mm2px(Vec(39.352, 102.469)), module, Snare::AUTONOTCH_PARAM));
    addParam(createParamCentered<KnobSmallDirectional>(mm2px(Vec(53.93, 106.438)), module, Snare::MASTERAMP_PARAM));
    addParam(createParamCentered<KnobSmallDirectional>(mm2px(Vec(10.387, 110.142)), module, Snare::NOTCH1_PARAM));
    addParam(createParamCentered<KnobSmallDirectional>(mm2px(Vec(20.335, 110.142)), module, Snare::NOTCH2_PARAM));
    addParam(createParamCentered<KnobSmallDirectional>(mm2px(Vec(30.283, 110.142)), module, Snare::NOTCH3_PARAM));
    addParam(createParamCentered<KnobSmallDirectional>(mm2px(Vec(15.348, 122.842)), module, Snare::LPF_PARAM));
    addParam(createParamCentered<KnobSmallDirectional>(mm2px(Vec(25.296, 122.842)), module, Snare::HPF_PARAM));

    addInput(createInputCentered<DSIPort>(mm2px(Vec(39.526, 5.899)), module, Snare::MOD0_INPUT));
    addInput(createInputCentered<DSIPort>(mm2px(Vec(45.48, 5.899)), module, Snare::MOD1_INPUT));
    addInput(createInputCentered<DSIPort>(mm2px(Vec(51.434, 5.899)), module, Snare::MOD2_INPUT));
    addInput(createInputCentered<DSIPort>(mm2px(Vec(57.388, 5.899)), module, Snare::MOD3_INPUT));
    addInput(createInputCentered<DSIPort>(mm2px(Vec(43.858, 122.845)), module, Snare::TRIGGER_INPUT));

    addOutput(createOutputCentered<DSOPort>(mm2px(Vec(52.879, 122.842)), module, Snare::OUTPUT_OUTPUT));

    // mm2px(Vec(12.446, 78.846))
    // addChild(createWidget<Widget>(mm2px(Vec(46.741, 18.256))));
    ModMatrixWidget *MatrixDisplay = new ModMatrixWidget();
    MatrixDisplay->box.pos = mm2px(Vec(46.741, 18.256));
    MatrixDisplay->box.size = mm2px(Vec(12.446, 78.846));
    if (module)
        MatrixDisplay->setEngine(module->engine);
    addChild(MatrixDisplay);


}