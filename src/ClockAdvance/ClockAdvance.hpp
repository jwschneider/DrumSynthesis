#pragma once
#include <engine/Module.hpp>
#include <app/ModuleWidget.hpp>
#include "ClockAdvanceEngine.hpp"
#include "../plugin.hpp"

namespace clockAdvance {
    class ClockAdvance : public Module {
        public:
            ClockAdvance();
            enum ParamIds {
                BEATSNUMERATOR_PARAM,
                BEATSDENOMINATOR_PARAM,
                SWITCH_PARAM,
                MS_PARAM,
                NUM_PARAMS
            };
            enum InputIds {
                CLOCK_INPUT,
                NUM_INPUTS
            };
            enum OutputIds {
                TRIGGER_OUTPUT,
                NUM_OUTPUTS
            };
            enum LightIds {
                NUM_LIGHTS
            };
            void process(const ProcessArgs& args) override;

        private:
            ClockAdvanceEngine *engine;
    };

class ClockAdvancePanel : public ModuleWidget {
    public:
        ClockAdvancePanel(ClockAdvance *clockAdvance);
};
} //namespace clockAdvance