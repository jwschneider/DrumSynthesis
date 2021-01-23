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
    initHead(sampleRate);
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
    lowDecay.init(1.f / (2*fun), decay, 0.f, 0.f, sampleRate);
}

void KickEngine::initMids(float sampleRate)
{
    float tone = controls->getMidTone();
    float character = controls->getMidCharacter();
    midModIndex = 8.f;
    midOscillator = FMOscillator(tone, character, midModIndex);
    float decay = controls->getMidDecay();
    midDecay.init(1.f/(4.f*tone), decay, 0.0, 0.0, sampleRate);
    midModDecay.init(1.f/(4.f*character), decay * 2.f / 3.f, 0.5, 0.f, sampleRate);
    midLPF.setCutoff(controls->getMidLP());
    midHPF.setCutoff(controls->getMidHP());
}

void KickEngine::initHead(float sampleRate)
{
    float tone = controls->getHeadTone();
    float character = controls->getHeadCharacter();
    headModIndex = 8.f;
    headOscillator = FMOscillator(tone, character, headModIndex);
    float decay = controls->getHeadDecay();
    headDecay.init(1.f/(4.f*tone), decay, 0.0, 0.0, sampleRate);
    headModDecay.init(1.f/(4.f*character), decay * 2.f / 3.f, 0.5, 0.f, sampleRate);
    headLPF.setCutoff(controls->getHeadLP());
    headHPF.setCutoff(controls->getHeadHP());
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
    headOscillator.reset();
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
    acc *= lowDecay.getValue() * 4.f; // makeup gain
    acc *= controls->getLowLevel();
    return acc;
}

float KickEngine::processMids(float sampleRate, float sampleTime)
{
    midModDecay.process(sampleRate, sampleTime);
    midOscillator.setModIndex(midModIndex * midModDecay.getValue());
    midOscillator.process(sampleRate, sampleTime);
    midDecay.process(sampleRate, sampleTime);
    midLPF.process(midOscillator.getImaginary(), sampleTime);
    midHPF.process(midLPF.lowpass(), sampleTime);
    return midHPF.highpass() * midDecay.getValue() * controls->getMidLevel() * 5.f; 
}

float KickEngine::processHead(float sampleRate, float sampleTime)
{
    headModDecay.process(sampleRate, sampleTime);
    headOscillator.setModIndex(headModIndex * headModDecay.getValue());
    headOscillator.process(sampleRate, sampleTime);
    headDecay.process(sampleRate, sampleTime);
    headLPF.process(headOscillator.getImaginary(), sampleTime);
    headHPF.process(headLPF.lowpass(), sampleTime);
    return headHPF.highpass() * headDecay.getValue() * controls->getHeadLevel() * 5.f; 
}

void KickEngine::process(float sampleRate, float sampleTime) {
    updateState(sampleRate, sampleTime);
    if (_ON) {
        float out = 0;
        out += processLows(sampleRate, sampleTime);
        out += processMids(sampleRate, sampleTime);
        out += processHead(sampleRate, sampleTime);
        controls->setOutputVoltage(out);
    }
}

