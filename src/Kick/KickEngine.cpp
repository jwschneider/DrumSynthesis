#include "KickEngine.hpp"
#include "../common/PercussionEngine.hpp"

using namespace kick;

float scaleFrequency(float freq, float fundamental, float spread, int partials, float bend)
{
    if (partials > 1)
    {
        float lambda = -std::log(bend) / (spread * (partials - 1));
        return std::exp(-lambda * (freq - fundamental));
    }
    else return 1.f;
}

class Low : public PercussionSection
{
    public:
    Low(KickControls *controls) 
    {
        this->controls = controls;
    }
    ~Low()
    {
        reset();
    }
    void init(float sampleRate) override
    {
        float fun = controls->getFundamentalFQ();
        int partials = controls->getPartials();
        float spread = controls->getFQSpread();
        float bend = controls->getBend();
        float totalMag = 0.f;
        for (int i = 0; i < partials; i++)
        {
            float frequency = fun + spread * i;
            SimpleOscillator *osc = new SimpleOscillator(frequency);
            float magnitude = scaleFrequency(frequency, fun, spread, partials, bend);
            osc->setMagnitude(magnitude);
            totalMag += magnitude;
            oscillators.push_back(osc);
        }
        for (vector<SimpleOscillator*>::iterator iter = oscillators.begin(); iter != oscillators.end(); ++iter)
        {
            (*iter)->setMagnitude((*iter)->getMagnitude() / (totalMag));
        }
        float decay = controls->getLowDecay();
        decayEnvelope.init(1.f / (2*fun), decay, 0.f, 0.f, sampleRate);
    }
    float process(float sampleRate, float sampleTime) override
    {
        float acc = 0;
        for (vector<SimpleOscillator*>::iterator iter = oscillators.begin(); iter != oscillators.end(); ++iter)
        {
            (*iter)->process(sampleRate, sampleTime);
            acc += (*iter)->getImaginary();
        }
        decayEnvelope.process(sampleRate, sampleTime);
        acc *= decayEnvelope.getValue() * 4.f; // makeup gain
        acc *= controls->getLowLevel();
        return acc;
    }
    void reset() override
    {
        while (!oscillators.empty())
        {
            delete oscillators.back();
            oscillators.pop_back();
        }
    }
    private:
    EnvelopeGenerator decayEnvelope;
    vector<SimpleOscillator*> oscillators;
    KickControls *controls;
};

class Mid : public PercussionSection
{
    public:
    Mid(KickControls *controls)
    {
        this->controls = controls;
    }
    ~Mid()
    {

    }
    void init(float sampleRate) override
    {
        float tone = controls->getMidTone();
        float character = controls->getMidCharacter();
        modIndex = 8.f;
        oscillator = FMOscillator(tone, character, modIndex);
        float decay = controls->getMidDecay();
        decayEnvelope.init(1.f/(4.f*tone), decay, 0.0, 0.0, sampleRate);
        modDecayEnvelope.init(1.f/(4.f*character), decay * 2.f / 3.f, 0.5, 0.f, sampleRate);
        LPF.setCutoff(controls->getMidLP());
        HPF.setCutoff(controls->getMidHP());
    }
    float process(float sampleRate, float sampleTime) override
    {
        modDecayEnvelope.process(sampleRate, sampleTime);
        oscillator.setModIndex(modIndex * modDecayEnvelope.getValue());
        oscillator.process(sampleRate, sampleTime);
        decayEnvelope.process(sampleRate, sampleTime);
        LPF.process(oscillator.getImaginary(), sampleTime);
        HPF.process(LPF.lowpass(), sampleTime);
        return HPF.highpass() * decayEnvelope.getValue() * controls->getMidLevel() * 5.f; 
    }
    void reset() override
    {
        oscillator.reset();
    }
    private:
    FMOscillator oscillator;
    EnvelopeGenerator decayEnvelope;
    float modIndex;
    EnvelopeGenerator modDecayEnvelope;
    LadderFilter<float> LPF;
    LadderFilter<float> HPF;
    KickControls *controls;
};

class Head : public PercussionSection
{
    public:
    Head(KickControls *controls)
    {
        this->controls = controls;
    }
    ~Head()
    {

    }
    void init(float sampleRate) override
    {
        float tone = controls->getHeadTone();
        float character = controls->getHeadCharacter();
        modIndex = 8.f;
        oscillator = FMOscillator(tone, character, modIndex);
        float decay = controls->getHeadDecay();
        decayEnvelope.init(1.f/(4.f*tone), decay, 0.0, 0.0, sampleRate);
        modDecayEnvelope.init(1.f/(4.f*character), decay * 2.f / 3.f, 0.5, 0.f, sampleRate);
        LPF.setCutoff(controls->getHeadLP());
        HPF.setCutoff(controls->getHeadHP());
    }
    float process(float sampleRate, float sampleTime) override
    {
        modDecayEnvelope.process(sampleRate, sampleTime);
        oscillator.setModIndex(modIndex * modDecayEnvelope.getValue());
        oscillator.process(sampleRate, sampleTime);
        decayEnvelope.process(sampleRate, sampleTime);
        LPF.process(oscillator.getImaginary(), sampleTime);
        HPF.process(LPF.lowpass(), sampleTime);
        return HPF.highpass() * decayEnvelope.getValue() * controls->getHeadLevel() * 5.f;
    }
    void reset() override
    {
        oscillator.reset();
    }
    private:
    FMOscillator oscillator;
    float modIndex;
    EnvelopeGenerator modDecayEnvelope;
    EnvelopeGenerator decayEnvelope;
    LadderFilter<float> LPF;
    LadderFilter<float> HPF;
    KickControls *controls;
};



KickEngine::KickEngine(KickControls *controls) : PercussionEngine(controls)
{
    sections.push_back(new Low(controls));
    sections.push_back(new Mid(controls));
    sections.push_back(new Head(controls));
}


