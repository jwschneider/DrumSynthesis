#include "KickEngine.hpp"

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

// Manages _ON sets up and tears down state
void KickEngine::updateState(float sampleRate, float sampleTime)
{
    bool trig = trigger.process(controls->getTrigger());
    if (trig)
    {
        reset();
        init(sampleRate);
        _ON = true;
        _currentTime = 0.f;
        _endTime = controls->getLongestDecay();
    }
    else if (_ON)
    {
        _currentTime += sampleTime;
        _ON = _currentTime < _endTime;
    }
    else
    {
        reset();
    }
}

// Assumes a clean slate
void KickEngine::init(float sampleRate)
{
    initLows(sampleRate);
    initMids(sampleRate);
}

void KickEngine::initLows(float sampleRate)
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
        lowOscillators.push_back(osc);
    }
    for (vector<SimpleOscillator*>::iterator iter = lowOscillators.begin(); iter != lowOscillators.end(); ++iter)
    {
        (*iter)->setMagnitude((*iter)->getMagnitude() / (totalMag));
    }
    float decay = controls->getLowDecay();
    lowDecay.init(decay, sampleRate);
}

void KickEngine::initMids(float sampleRate)
{
    float tone = controls->getMidTone();
    float character = controls->getMidCharacter();
    midModIndex = 8.f;
    midOscillator = FMOscillator(tone, character, midModIndex);
    float decay = controls->getMidDecay();
    midDecay.init(decay, sampleRate);
    midModDecay.init(decay * 2.f / 3.f, sampleRate);
    midLPF.setCutoff(controls->getMidLP());
    midHPF.setCutoff(controls->getMidHP());
}

// Cleans the slate
void KickEngine::reset()
{
    while (!lowOscillators.empty())
    {
        delete lowOscillators.back();
        lowOscillators.pop_back();
    }
    midOscillator.reset();
}

float KickEngine::processLows(float sampleRate, float sampleTime)
{
    float acc = 0;
    for (vector<SimpleOscillator*>::iterator iter = lowOscillators.begin(); iter != lowOscillators.end(); ++iter)
    {
        (*iter)->process(sampleRate, sampleTime);
        acc += (*iter)->getImaginary();
    }
    lowDecay.process(sampleRate, sampleTime);
    acc *= lowDecay.getValue();
    acc *= controls->getLowLevel();
    return acc;
}

float KickEngine::processMids(float sampleRate, float sampleTime)
{
    // midModulator.setFrequency(controls->getMidCharacter());
    // midCarrier.setFrequency(rack::dsp::FREQ_A4 * (controls->getMidToneVoltage() + midOscillators[1]->getImaginary()));
    // midModulator.process(sampleRate, sampleTime);
    // midCarrier.process(sampleRate, sampleTime);
    midModDecay.process(sampleRate, sampleTime);
    midOscillator.setModIndex(midOscillator.getModIndex() * midModDecay.getValue());
    midOscillator.process(sampleRate, sampleTime);
    midDecay.process(sampleRate, sampleTime);
    midLPF.process(midOscillator.getImaginary(), sampleTime);
    midHPF.process(midLPF.lowpass(), sampleTime);
    return midHPF.highpass() * midDecay.getValue() * controls->getMidLevel(); 
}

float KickEngine::processHighs(float sampleRate, float sampleTime)
{
    return 0;
}

void KickEngine::process(float sampleRate, float sampleTime) {
    updateState(sampleRate, sampleTime);
    if (_ON) {
        float out = 0;
        out += processLows(sampleRate, sampleTime);
        out += processMids(sampleRate, sampleTime);
        out += processHighs(sampleRate, sampleTime);
        controls->setOutputVoltage(out);
    }
}

