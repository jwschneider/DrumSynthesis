// http://www.martin-finke.de/blog/articles/audio-plugins-011-envelopes/
#include <cmath>

using namespace std;

class DecayEnvelope {
    public:
        DecayEnvelope() = default;
        void init(float duration, float sampleRate)
        {
            this->sampleRate = sampleRate;
            currentLevel = 1.f;
            multiplier = 1.0 + log(minimumLevel)/(sampleRate * duration);
        }
        void process(float sampleRate, float sampleTime)
        {
            for (int i = 0; i < std::floor(sampleRate * sampleTime); i++)
            {
                nextSample();
            }
        }
        float getValue()
        {
            return currentLevel;
        }
    private:
        float nextSample() {
            currentLevel *= multiplier;
            return currentLevel;
        }
        const float minimumLevel = 0.0001;
        float currentLevel;
        float multiplier;
        float sampleRate;
};