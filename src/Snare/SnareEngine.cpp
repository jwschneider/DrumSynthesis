#include "SnareEngine.hpp"
#include "SnareControls.hpp"
#include "Snare.hpp"
#include "../common/SimpleOscillator.hpp"
#include "../common/EnvelopeGenerator.hpp"
#include "../common/Oscillator.hpp"

using namespace snare;

class Base : public PercussionSection
{
    public:
    Base(SnareControls *controls) 
    {
        this->controls = controls;
    }
    ~Base()
    {

    }
    void init(float sampleRate) override
    {
        float freq1 = controls->getBaseFQ();
        float freq2 = freq1 * 1.8;
        osc1 = SimpleOscillator(freq1);
        osc2 = SimpleOscillator(freq2);
        float decay = controls->getBaseDecay();
        decayEnvelope.init(1.f/(4.f*freq1), decay, 0.f, 0.f, sampleRate);
    }
    float process(float sampleRate, float sampleTime) override
    {
        osc1.process(sampleRate, sampleTime);
        osc2.process(sampleRate, sampleTime);
        decayEnvelope.process(sampleRate, sampleTime);
        return (osc1.getImaginary() + osc2.getImaginary()) * decayEnvelope.getValue() * controls->getBaseAmp();
    }
    void reset() override
    {
        osc1.reset();
        osc2.reset();
    }
    private:
    SimpleOscillator osc1;
    SimpleOscillator osc2;
    EnvelopeGenerator decayEnvelope;
    SnareControls *controls;
};

class Harmonic : public PercussionSection
{
    public:
    Harmonic(SnareControls *controls)
    {
        this->controls = controls;
    }
    ~Harmonic()
    {

    }
    void init(float sampleRate) override
    {
        a_phase = 0.f;
        w1_phase = 0.f;
        w2_phase = 0.f;
    }
    float process(float sampleRate, float sampleTime) override
    {
        updateFrequency();
        updatePhase(sampleTime);
        float out = output();
        controls->setOutputVoltage(out);
    }
    void reset() override
    {
        a_phase = 0.f;
        w1_phase = 0.f;
        w2_phase = 0.f;
    }
    private:
    float output()
    {
        float out = 0.f;
        out += (Oscillator::cos(w1_phase)+Oscillator::cos(w2_phase)) * Oscillator::tri(a_phase);
        for (int n = -3; n <= 3; n++)
        {
            out += (Oscillator::sin(w1_phase) + Oscillator::sin(w2_phase))
                * (2.f * Oscillator::hilbert_tri(a_phase - 0.25 * (1.f + 4.f * n)) - 1);
        }
        return out;
    }
    void updatePhase(float sampleTime)
    {
        a_phase += a * sampleTime;
        a_phase -= floor(a_phase);
        w1_phase += w1 * sampleTime;
        w1_phase -= floor(w1_phase);
        w2_phase += w2 * sampleTime;
        w2_phase -= floor(w2_phase);
    }
    void updateFrequency()
    {
        a = controls->getTriangleFQ();
        w1 = controls->getHarmonic1() - a;
        w2 = controls->getHarmonic2() - a;
    }
    SnareControls *controls;
    float a;
    float a_phase;
    float w1;
    float w1_phase;
    float w2;
    float w2_phase;
};

SnareEngine::SnareEngine(SnareControls *controls) : PercussionEngine(controls)
{
    sections.push_back(new Base(controls));
    sections.push_back(new Harmonic(controls));
}

SnareControls *SnareEngine::getControls()
{
    return (SnareControls *) controls;
}
