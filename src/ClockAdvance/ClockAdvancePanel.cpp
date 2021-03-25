#include "ClockAdvance.hpp"
#include "../common/Components.hpp"
#include <sstream>
#include <iomanip>

using namespace rack;
using namespace clockAdvance;

extern Plugin* plugininstance;

class IntegerDisplayWidget : public TransparentWidget {
    public:
    std::string *value = NULL;
    std::shared_ptr<Font> font;
    IntegerDisplayWidget() {
        font = APP->window->loadFont(asset::plugin(pluginInstance, "res/clacon.ttf"));
    }
    void draw(const DrawArgs &args) override {
        if (!value)
            return;
        nvgFontSize(args.vg, 20);
        nvgFontFaceId(args.vg, font->handle);
        nvgTextLetterSpacing(args.vg, 2.5);
        std::stringstream to_display;   
        to_display << std::setw(3) << *value;
        Vec textPos = Vec(0.f, 14.5f);
        NVGcolor textcolor = nvgRGB(0x16, 0xb2, 0x16);
        nvgFillColor(args.vg, textcolor);
        nvgText(args.vg, textPos.x, textPos.y, to_display.str().c_str(), NULL);
    }
};

clockAdvance::ClockAdvancePanel::ClockAdvancePanel(ClockAdvance *module) {
    setModule(module);
    setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/Advance.svg")));

    addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
    addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
    addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
    addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

    addParam(createParamCentered<SnapKnobSmallNonDirectional>(mm2px(Vec(7.136, 48.941)), module, ClockAdvance::NOTESNUMERATOR_PARAM));
    addParam(createParamCentered<SnapKnobSmallNonDirectional>(mm2px(Vec(7.136, 59.429)), module, ClockAdvance::NOTESDENOMINATOR_PARAM));
    addParam(createParam<DSSwitch>(mm2px(Vec(12.7, 68.792)), module, ClockAdvance::SWITCH_PARAM));
    addParam(createParamCentered<SnapKnobSmallNonDirectional>(mm2px(Vec(7.136, 85.956)), module, ClockAdvance::MS_PARAM));

    addInput(createInputCentered<DSIPort>(mm2px(Vec(7.136, 29.837)), module, ClockAdvance::CLOCK_INPUT));

    addOutput(createOutputCentered<DSOPort>(mm2px(Vec(20.955, 118.431)), module, ClockAdvance::TRIGGER_OUTPUT));

    IntegerDisplayWidget *BPMDisplay = new IntegerDisplayWidget();
    BPMDisplay->box.pos = mm2px(Vec(15.24, 26.458));
    BPMDisplay->box.size = mm2px(Vec(11.43, 5.292));
    if (module)
        BPMDisplay->value = &module->engine->strBPM;
    addChild(BPMDisplay);
    // mm2px(Vec(11.43, 5.292))
    //addChild(createWidget<Widget>(mm2px(Vec(15.24, 26.458))));

    IntegerDisplayWidget *NotesNumDisplay = new IntegerDisplayWidget();
    NotesNumDisplay->box.pos = mm2px(Vec(15.24, 46.302));
    NotesNumDisplay->box.size = mm2px(Vec(11.43, 5.292));
    if (module)
        NotesNumDisplay->value = &module->engine->strNotesNum;
    addChild(NotesNumDisplay);
    // mm2px(Vec(11.43, 5.292))
    //addChild(createWidget<Widget>(mm2px(Vec(15.24, 46.302))));

    IntegerDisplayWidget *NotesDenomDisplay = new IntegerDisplayWidget();
    NotesDenomDisplay->box.pos = mm2px(Vec(15.24, 56.885));
    NotesDenomDisplay->box.size = mm2px(Vec(11.43, 5.292));
    if (module)
        NotesDenomDisplay->value = &module->engine->strNotesDenom;
    addChild(NotesDenomDisplay);
    // mm2px(Vec(11.43, 5.292))
    //addChild(createWidget<Widget>(mm2px(Vec(15.24, 56.885))));

    IntegerDisplayWidget *MSDisplay = new IntegerDisplayWidget();
    MSDisplay->box.pos = mm2px(Vec(15.24, 83.344));
    MSDisplay->box.size = mm2px(Vec(11.43, 5.292));
    if (module)
        MSDisplay->value = &module->engine->strMS;
    addChild(MSDisplay);
    // mm2px(Vec(11.43, 5.292))
    //addChild(createWidget<Widget>(mm2px(Vec(15.24, 83.344))));
}