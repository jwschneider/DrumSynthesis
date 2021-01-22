// http://www.martin-finke.de/blog/articles/audio-plugins-011-envelopes/
#include <cmath>

using namespace std;

class DecayEnvelope {
    public:
        DecayEnvelope() = default;
        virtual ~DecayEnvelope() {};
        virtual void init(float duration, float sampleRate)
        {
            this->sampleRate = sampleRate;
            currentLevel = 1.f;
            multiplier = 1.0 + log(minimumLevel)/(sampleRate * duration);
        }
        virtual void process(float sampleRate, float sampleTime)
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
    protected:
        const float minimumLevel = 0.01;
        float currentLevel;
        float multiplier;
        float sampleRate;
    private:
        float nextSample() {
            currentLevel *= multiplier;
            return currentLevel;
        }
};