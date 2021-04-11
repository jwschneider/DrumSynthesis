#include "SnareEngine.hpp"
#include "SnareControls.hpp"
#include "Snare.hpp"
#include "../common/SimpleOscillator.hpp"
#include "../common/EnvelopeGenerator.hpp"

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

SnareEngine::SnareEngine(SnareControls *controls) : PercussionEngine(controls)
{
    sections.push_back(new Base(controls));
}

SnareControls *SnareEngine::getControls()
{
    return (SnareControls *) controls;
}
