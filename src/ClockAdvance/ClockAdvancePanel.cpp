#include "ClockAdvance.hpp"
#include "../common/Components.hpp"

using namespace rack;
using namespace clockAdvance;

extern Plugin* plugininstance;

clockAdvance::ClockAdvancePanel::ClockAdvancePanel(ClockAdvance *module) {
    setModule(module);
    setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/Advance.svg")));

    addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
    addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
    addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
    addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

    addParam(createParamCentered<SnapKnobSmallNonDirectional>(mm2px(Vec(7.136, 48.941)), module, ClockAdvance::BEATSNUMERATOR_PARAM));
    addParam(createParamCentered<SnapKnobSmallNonDirectional>(mm2px(Vec(7.136, 59.429)), module, ClockAdvance::BEATSDENOMINATOR_PARAM));
    addParam(createParam<DSSwitch>(mm2px(Vec(12.7, 68.792)), module, ClockAdvance::SWITCH_PARAM));
    addParam(createParamCentered<SnapKnobSmallNonDirectional>(mm2px(Vec(7.136, 85.956)), module, ClockAdvance::MS_PARAM));

    addInput(createInputCentered<DSIPort>(mm2px(Vec(7.136, 29.837)), module, ClockAdvance::CLOCK_INPUT));

    addOutput(createOutputCentered<DSOPort>(mm2px(Vec(20.955, 118.431)), module, ClockAdvance::TRIGGER_OUTPUT));

    // mm2px(Vec(11.43, 5.292))
    addChild(createWidget<Widget>(mm2px(Vec(15.24, 26.458))));
    // mm2px(Vec(11.43, 5.292))
    addChild(createWidget<Widget>(mm2px(Vec(15.24, 46.302))));
    // mm2px(Vec(11.43, 5.292))
    addChild(createWidget<Widget>(mm2px(Vec(15.24, 56.885))));
    // mm2px(Vec(11.43, 5.292))
    addChild(createWidget<Widget>(mm2px(Vec(15.24, 83.344))));
}