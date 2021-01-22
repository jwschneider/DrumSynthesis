#pragma once
#include "../common/ModuleEngine.hpp"
#include "KickControls.hpp"
#include "../common/FMOscillator.hpp"
#include "../common/LinearDecayEnvelope.hpp"
#include <dsp/digital.hpp>
#include <dsp/filter.hpp>
#include "../common/Filter.hpp"

using namespace rack::dsp;

namespace kick{

    class KickEngine : ModuleEngine {
        KickControls *controls;
        public:
        KickEngine(KickControls *controls)
        {
            this->controls = controls;
            _ON = false;
        }
        ~KickEngine()
        {
            reset();
            delete controls;
        }
        void process(float sampleRate, float sampleTime) override;
        // public for testing purposes
        DecayEnvelope lowDecay;
        vector<SimpleOscillator*> lowOscillators;
        FMOscillator midOscillator;
        DecayEnvelope midDecay;
        float midModIndex;
        DecayEnvelope midModDecay;
        LadderFilter<float> midLPF;
        LadderFilter<float> midHPF;

        private:
        float phase = 0.f;
        float processLows(float sampleRate, float sampleTime);
        float processMids(float sampleRate, float sampleTime);
        float processHighs(float sampleRate, float sampleTime);
        void init(float sampleRate);
        void initLows(float sampleRate);
        void initMids(float sampleRate);
        void initHighs(float sampleRate);
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
        rack::dsp::SchmittTrigger trigger;
    };
} //namespace Kick