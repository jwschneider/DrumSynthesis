#pragma once
#include "../common/ModuleEngine.hpp"
#include "SnareControls.hpp"

namespace snare {
    class SnareEngine : ModuleEngine {
        SnareControls *controls;
        public:
        SnareEngine(SnareControls *controls, int numParams)
        {
            this->controls = controls;
            _modMatrix = new int*[numParams];
            for (int i = 0; i < numParams; i++)
            {
                _modMatrix[i] = new int[5] {0};
            }
        }
        ~SnareEngine()
        {
            delete controls;
            // for (int i = 0; i < sizeof(_modMatrix); i++)
            // {
            //     delete _modMatrix[i];
            // }   
            delete[] _modMatrix;
        }
        void process(float sampleRate, float sampleTime) override;
        int **_modMatrix;       
    };
}