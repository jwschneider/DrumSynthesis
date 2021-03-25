#pragma once
#include "../common/ModuleEngine.hpp"
#include "ClockAdvanceControls.hpp"

namespace clockAdvance {
    class ClockAdvanceEngine : ModuleEngine {
        ClockAdvanceControls *controls;
        public:
        ClockAdvanceEngine(ClockAdvanceControls *controls)
        {
            this->controls = controls;
        }
        ~ClockAdvanceEngine()
        {
            delete controls;
        }
        void process(float sampleRate, float sampleTime) override;
    };
}