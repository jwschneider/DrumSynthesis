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
        (*iter)->setMagnitude((*iter)->getMagnitude() / totalMag);
    }
    float decay = controls->getLowDecay();
    lowDecay.init(decay, sampleRate);
}

void KickEngine::initMids(float sampleRate)
{
    float tone = controls->getMidTone();
    float character = controls->getMidCharacter();
    midOscillators[0] = new SimpleOscillator(tone);
    midOscillators[1] = new SimpleOscillator(character);
    float decay = controls->getMidDecay();
    midDecay.init(decay, sampleRate);
}

// Cleans the slate
void KickEngine::reset()
{
    while (!lowOscillators.empty())
    {
        delete lowOscillators.back();
        lowOscillators.pop_back();
    }
    if (midOscillators[0] != NULL) delete midOscillators[0];
    if (midOscillators[1] != NULL) delete midOscillators[1];
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
    midOscillators[1]->setFrequency(controls->getMidCharacter());
    midOscillators[0]->setFrequency(rack::dsp::FREQ_A4 * (controls->getMidToneVoltage() + midOscillators[1]->getImaginary()));
    midOscillators[1]->process(sampleRate, sampleTime);
    midOscillators[0]->process(sampleRate, sampleTime);
    midDecay.process(sampleRate, sampleTime);
    return midOscillators[0]->getImaginary() * midDecay.getValue() * controls->getMidLevel(); 
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

