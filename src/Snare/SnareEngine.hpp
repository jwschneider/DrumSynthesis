#pragma once
#include "../common/ModuleEngine.hpp"
#include "SnareControls.hpp"

namespace snare {
    class SnareEngine : ModuleEngine {
        SnareControls *controls;
        public:
        SnareEngine(SnareControls *controls)
        {
            this->controls = controls;
        }
        ~SnareEngine()
        {
            delete controls;
        }
        void process(float sampleRate, float sampleTime) override;
    };
}