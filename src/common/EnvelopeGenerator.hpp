// http://www.martin-finke.de/blog/articles/audio-plugins-011-envelopes/
// This is not my code. This was written by and belongs to Martin Finke

#include <cmath>

class EnvelopeGenerator {
public:
    enum EnvelopeStage {
        ENVELOPE_STAGE_OFF = 0,
        ENVELOPE_STAGE_ATTACK,
        ENVELOPE_STAGE_DECAY,
        ENVELOPE_STAGE_SUSTAIN,
        ENVELOPE_STAGE_RELEASE,
        kNumEnvelopeStages
    };
    void enterStage(EnvelopeStage newStage);
    double nextSample();
    void setSampleRate(double newSampleRate);
    inline EnvelopeStage getCurrentStage() const { return currentStage; };
    const double minimumLevel;

    EnvelopeGenerator() :
    minimumLevel(0.01),
    currentStage(ENVELOPE_STAGE_OFF),
    currentLevel(minimumLevel),
    multiplier(1.0),
    sampleRate(44100.0),
    currentSampleIndex(0),
    nextStageSampleIndex(0) {
        stageValue[ENVELOPE_STAGE_OFF] = 0.0;
        stageValue[ENVELOPE_STAGE_ATTACK] = 0.01;
        stageValue[ENVELOPE_STAGE_DECAY] = 0.5;
        stageValue[ENVELOPE_STAGE_SUSTAIN] = 0.1;
        stageValue[ENVELOPE_STAGE_RELEASE] = 1.0;
    };

    void init(float attack, float decay, float sustain, float release, float sampleRate)
    {
        stageValue[ENVELOPE_STAGE_OFF] = 0.0;
        stageValue[ENVELOPE_STAGE_ATTACK] = attack;
        stageValue[ENVELOPE_STAGE_DECAY] = decay;
        stageValue[ENVELOPE_STAGE_SUSTAIN] = sustain;
        stageValue[ENVELOPE_STAGE_RELEASE] = release;
        this->sampleRate = sampleRate;
        enterStage(ENVELOPE_STAGE_ATTACK);
    }
    void process(float sampleRate, float sampleTime)
    {
        for (float i = 0; i < sampleTime; i+= 1.f/sampleRate)
        {
            nextSample();
        }
    }
    float getValue()
    {
        return currentLevel;
    }

private:
    EnvelopeStage currentStage;
    double currentLevel;
    double multiplier;
    double sampleRate;
    double stageValue[kNumEnvelopeStages];
    void calculateMultiplier(double startLevel, double endLevel, unsigned long long lengthInSamples);
    unsigned long long currentSampleIndex;
    unsigned long long nextStageSampleIndex;
};

void inline EnvelopeGenerator::calculateMultiplier(double startLevel,
                                            double endLevel,
                                            unsigned long long lengthInSamples) {
    multiplier = 1.0 + (log(endLevel) - log(startLevel)) / (lengthInSamples);
}

void inline EnvelopeGenerator::enterStage(EnvelopeStage newStage) {
    currentStage = newStage;
    currentSampleIndex = 0;
    if (currentStage == ENVELOPE_STAGE_OFF ||
        currentStage == ENVELOPE_STAGE_SUSTAIN) {
        nextStageSampleIndex = 0;
    } else {
        nextStageSampleIndex = stageValue[currentStage] * sampleRate;
    }
    switch (newStage) {
        case ENVELOPE_STAGE_OFF:
            currentLevel = 0.0;
            multiplier = 1.0;
            break;
        case ENVELOPE_STAGE_ATTACK:
            currentLevel = minimumLevel;
            calculateMultiplier(currentLevel,
                                1.0,
                                nextStageSampleIndex);
            break;
        case ENVELOPE_STAGE_DECAY:
            currentLevel = 1.0;
            calculateMultiplier(currentLevel,
                                fmax(stageValue[ENVELOPE_STAGE_SUSTAIN], minimumLevel),
                                nextStageSampleIndex);
            break;
        case ENVELOPE_STAGE_SUSTAIN:
            currentLevel = stageValue[ENVELOPE_STAGE_SUSTAIN];
            multiplier = 1.0;
            break;
        case ENVELOPE_STAGE_RELEASE:
            // We could go from ATTACK/DECAY to RELEASE,
            // so we're not changing currentLevel here.
            calculateMultiplier(currentLevel,
                                minimumLevel,
                                nextStageSampleIndex);
            break;
        default:
            break;
    }
}

double inline EnvelopeGenerator::nextSample() {
    if (currentStage != ENVELOPE_STAGE_OFF &&
        currentStage != ENVELOPE_STAGE_SUSTAIN) {
        if (currentSampleIndex == nextStageSampleIndex) {
            EnvelopeStage newStage = static_cast<EnvelopeStage>(
                (currentStage + 1) % kNumEnvelopeStages
            );
            enterStage(newStage);
        }
        currentLevel *= multiplier;
        currentSampleIndex++;
    }
    return currentLevel;
}