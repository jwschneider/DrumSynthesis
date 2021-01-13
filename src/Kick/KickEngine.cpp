#include "KickEngine.hpp"

using namespace kick;

float scaleFrequency(float freq, float fundamental, float spread, int partials, float bend)
{
    return (1 + bend * (spread * (partials - 1) * freq + fundamental));
}

// Manages _ON sets up and tears down state
void KickEngine::updateState(float sampleRate, float sampleTime)
{
    if (!_ON)
    {
        if (trigger.process(controls->getTrigger()))
        {
            init(sampleRate);
            _ON = true;
            _currentTime = 0.f;
            _endTime = controls->getLongestDecay();
        }
    }
    else
    {
        _currentTime += sampleTime;
        _ON = _currentTime < _endTime;
        if (!_ON)
        {
            reset();
        }
    }
}

// Assumes a clean slate
void KickEngine::init(float sampleRate)
{
    float fun = controls->getFundamentalFQ();
    int partials = controls->getPartials();
    float spread = controls->getFQSpread();
    float bend = controls->getBend();
    for (int i = 0; i < partials; i++)
    {
        float frequency = fun + spread * i;
        SimpleOscillator *osc = new SimpleOscillator(frequency);
        osc->setMagnitude(scaleFrequency(frequency, fun, spread, partials, bend));
        lowOscillators.push_back(osc);
    }
    float decay = controls->getLowDecay();
    lowDecay.init(decay, sampleRate);
}

// Cleans the slate
void KickEngine::reset()
{
    while (!lowOscillators.empty())
    {
        delete lowOscillators.back();
        lowOscillators.pop_back();
    }
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
    return acc;
}

float KickEngine::processMids(float sampleRate, float sampleTime)
{
    return 0;
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

