#include "DecayEnvelope.hpp"

class LinearDecayEnvelope : public DecayEnvelope {
    public:
        LinearDecayEnvelope() = default;
        ~LinearDecayEnvelope() {};
        void init(float duration, float sampleRate) override
        {
            this->sampleRate = sampleRate;
            currentLevel = 1.f;
            multiplier = -1.f/duration;
        }
        void process(float sampleRate, float sampleTime) override
        {
            currentLevel = currentLevel + multiplier * sampleTime;
        }
};