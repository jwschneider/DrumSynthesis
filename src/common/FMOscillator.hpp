#pragma once
#include "SimpleOscillator.hpp"
#include <cmath>

class FMOscillator : public SimpleOscillator
{
    public:
        FMOscillator() : SimpleOscillator {}
        {
            modulator.setFrequency(0);
            modIndex = 1.f;
        }
        FMOscillator(float carrierFQ, float modulatorFQ, float mIndex) : SimpleOscillator { carrierFQ }
        {
            modulator.setFrequency(modulatorFQ);
            modIndex = mIndex;
        }
        ~FMOscillator() {}
        void process(float sampleRate, float sampleTime) override
        {
            modulator.process(sampleRate, sampleTime);
            phase += (modIndex / (2 * M_PI)) * modulator.getImaginary();
            phase += frequency * sampleTime;
            phase -= floor(phase);
        }
        void reset() override 
        {
            phase = 0.f;
            modulator.reset();
        }
        float getModFQ()
        {
            return modulator.getFrequency();
        }
        void setModFQ(float freq)
        {
            modulator.setFrequency(freq);
        }
        float getModIndex()
        {
            return modIndex;
        }
        void setModIndex(float index)
        {
            modIndex = index;
        }
    private:
        SimpleOscillator modulator;
        float modIndex;
};