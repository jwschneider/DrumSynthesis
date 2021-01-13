#pragma once
#include <engine/Module.hpp>
#include <app/ModuleWidget.hpp>
#include "KickEngine.hpp"
#include "../plugin.hpp"


namespace kick {

class Kick : public Module {
    public:
        Kick();
        enum ParamIds {
            LOW_FUNDAMENTAL_PARAM,
            LOW_PARTIALS_PARAM,
            LOW_SPREAD_PARAM,
            LOW_BEND_PARAM,
            LOW_DECAY_PARAM,
            LOW_LEVEL_PARAM,
            MID_TONE_PARAM,
            MID_CHARACTER_PARAM,
            MID_LP_PARAM,
            MID_HP_PARAM,
            MID_DECAY_PARAM,
            MID_LEVEL_PARAM,
            HEAD_TONE_PARAM,
            HEAD_CHARACTER_PARAM,
            HEAD_LP_PARAM,
            HEAD_HP_PARAM,
            HEAD_DECAY_PARAM,
            HEAD_LEVEL_PARAM,
            NUM_PARAMS
        };
        enum InputIds {
            LOW_FUNDAMENTAL_INPUT,
            LOW_PARTIALS_INPUT,
            LOW_SPREAD_INPUT,
            LOW_BEND_INPUT,
            LOW_DECAY_INPUT,
            LOW_LEVEL_INPUT,
            MID_TONE_INPUT,
            MID_CHARACTER_INPUT,
            MID_LP_INPUT,
            MID_HP_INPUT,
            MID_DECAY_INPUT,
            MID_LEVEL_INPUT,
            TRIG_INPUT,
            HEAD_TONE_INPUT,
            HEAD_CHARACTER_INPUT,
            HEAD_LP_INPUT,
            HEAD_HP_INPUT,
            HEAD_DECAY_INPUT,
            HEAD_LEVEL_INPUT,
            NUM_INPUTS
        };
        enum OutputIds {
            OUTPUT_OUTPUT,
            NUM_OUTPUTS
        };
        enum LightIds {
            NUM_LIGHTS
        };



	void process(const ProcessArgs& args) override;

    private:
        KickEngine *engine;
};


class KickPanel : public ModuleWidget {
    public:
        KickPanel(Kick *kick);
};
} //namespace Kick

