#pragma once
#include "ModuleControls.hpp"

class ModuleEngine {
    public:
        ModuleEngine() = default;
        virtual void process(float sampleRate, float sampleTime) = 0;
};