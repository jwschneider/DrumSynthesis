#include "Kick.hpp"

using namespace rack;
using namespace kick;

extern Plugin* pluginInstance;

kick::KickPanel::KickPanel(Kick *module) {
    setModule(module);
    setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/Kick.svg")));

    addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
    addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
    addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
    addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

    addParam(createParamCentered<RoundLargeBlackKnob>(mm2px(Vec(30.48, 21.417)), module, Kick::LOW_FUNDAMENTAL_PARAM));
    addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(50.8, 21.417)), module, Kick::LOW_PARTIALS_PARAM));
    addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(71.12, 21.417)), module, Kick::LOW_SPREAD_PARAM));
    addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(91.44, 21.417)), module, Kick::LOW_BEND_PARAM));
    addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(111.76, 21.417)), module, Kick::LOW_DECAY_PARAM));
    addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(132.08, 21.417)), module, Kick::LOW_LEVEL_PARAM));
    addParam(createParamCentered<RoundLargeBlackKnob>(mm2px(Vec(30.48, 64.25)), module, Kick::MID_TONE_PARAM));
    addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(50.8, 64.25)), module, Kick::MID_CHARACTER_PARAM));
    addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(71.12, 64.25)), module, Kick::MID_LP_PARAM));
    addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(91.44, 64.25)), module, Kick::MID_HP_PARAM));
    addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(111.76, 64.25)), module, Kick::MID_DECAY_PARAM));
    addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(132.08, 64.25)), module, Kick::MID_LEVEL_PARAM));
    addParam(createParamCentered<RoundLargeBlackKnob>(mm2px(Vec(30.48, 107.083)), module, Kick::HEAD_TONE_PARAM));
    addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(50.8, 107.083)), module, Kick::HEAD_CHARACTER_PARAM));
    addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(71.12, 107.083)), module, Kick::HEAD_LP_PARAM));
    addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(91.44, 107.083)), module, Kick::HEAD_HP_PARAM));
    addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(111.76, 107.083)), module, Kick::HEAD_DECAY_PARAM));
    addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(132.08, 107.083)), module, Kick::HEAD_LEVEL_PARAM));

    addInput(createInputCentered<PJ301MPort>(mm2px(Vec(30.48, 33.464)), module, Kick::LOW_FUNDAMENTAL_INPUT));
    addInput(createInputCentered<PJ301MPort>(mm2px(Vec(50.8, 33.464)), module, Kick::LOW_PARTIALS_INPUT));
    addInput(createInputCentered<PJ301MPort>(mm2px(Vec(71.12, 33.464)), module, Kick::LOW_SPREAD_INPUT));
    addInput(createInputCentered<PJ301MPort>(mm2px(Vec(91.44, 33.464)), module, Kick::LOW_BEND_INPUT));
    addInput(createInputCentered<PJ301MPort>(mm2px(Vec(111.76, 33.464)), module, Kick::LOW_DECAY_INPUT));
    addInput(createInputCentered<PJ301MPort>(mm2px(Vec(132.08, 33.464)), module, Kick::LOW_LEVEL_INPUT));
    addInput(createInputCentered<PJ301MPort>(mm2px(Vec(30.48, 76.297)), module, Kick::MID_TONE_INPUT));
    addInput(createInputCentered<PJ301MPort>(mm2px(Vec(50.8, 76.297)), module, Kick::MID_CHARACTER_INPUT));
    addInput(createInputCentered<PJ301MPort>(mm2px(Vec(71.12, 76.297)), module, Kick::MID_LP_INPUT));
    addInput(createInputCentered<PJ301MPort>(mm2px(Vec(91.44, 76.297)), module, Kick::MID_HP_INPUT));
    addInput(createInputCentered<PJ301MPort>(mm2px(Vec(111.76, 76.297)), module, Kick::MID_DECAY_INPUT));
    addInput(createInputCentered<PJ301MPort>(mm2px(Vec(132.08, 76.297)), module, Kick::MID_LEVEL_INPUT));
    addInput(createInputCentered<PJ301MPort>(mm2px(Vec(154.94, 102.629)), module, Kick::TRIG_INPUT));
    addInput(createInputCentered<PJ301MPort>(mm2px(Vec(30.48, 119.13)), module, Kick::HEAD_TONE_INPUT));
    addInput(createInputCentered<PJ301MPort>(mm2px(Vec(50.8, 119.13)), module, Kick::HEAD_CHARACTER_INPUT));
    addInput(createInputCentered<PJ301MPort>(mm2px(Vec(71.12, 119.13)), module, Kick::HEAD_LP_INPUT));
    addInput(createInputCentered<PJ301MPort>(mm2px(Vec(91.44, 119.13)), module, Kick::HEAD_HP_INPUT));
    addInput(createInputCentered<PJ301MPort>(mm2px(Vec(111.76, 119.13)), module, Kick::HEAD_DECAY_INPUT));
    addInput(createInputCentered<PJ301MPort>(mm2px(Vec(132.08, 119.13)), module, Kick::HEAD_LEVEL_INPUT));

    addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(154.94, 119.004)), module, Kick::OUTPUT_OUTPUT));
}