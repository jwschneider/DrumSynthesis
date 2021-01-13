#pragma once
#include "../ModuleEngine.hpp"
#include "KickControls.hpp"
#include "../SimpleOscillator.hpp"
#include "../DecayEnvelope.hpp"
#include <dsp/digital.hpp>

namespace kick{

    class KickEngine : ModuleEngine {
        KickControls *controls;
        public:
        KickEngine(KickControls *controls)
        {
            this->controls = controls;
        }
        void process(float sampleRate, float sampleTime) override;
        private:
        float phase = 0.f;
        float processLows(float sampleRate, float sampleTime);
        float processMids(float sampleRate, float sampleTime);
        float processHighs(float sampleRate, float sampleTime);
        void init(float sampleRate);
        void reset();
        void updateState(float sampleRate, float sampleTime);
        bool _ON;
        float _currentTime;
        float _endTime;
        // float _fundamental;
        // int _partials;
        // float _spread;
        // float _bend;
        // float _decay;
        DecayEnvelope lowDecay;
        vector<SimpleOscillator*> lowOscillators;
        rack::dsp::SchmittTrigger trigger;
    };
} //namespace Kick