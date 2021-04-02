#pragma once
#include "../common/ModuleEngine.hpp"
#include "SnareControls.hpp"

namespace snare {
    class SnareEngine : ModuleEngine {
        SnareControls *controls;
        public:
        SnareEngine(SnareControls *controls);
        ~SnareEngine();
        void process(float sampleRate, float sampleTime) override;
        int getModMatrixEntry(int i, int j);
        void toggleModMatrixEntry(int i, int j);
        int getModMatrixRowCount(int i);
        private:
        int **_modMatrix;       
    };
}