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
        json_t *modMatrixToJson();
        void modMatrixFromJson(json_t *modMatrix);
        private:
        void updateState(float sampleRate, float sampleTime);
        void processLows(float sampleRate, float sampleTime);
        int **_modMatrix;
        bool _ON;
        float _currentTime;
        float _endTime;       
    };
}