#include "ClockAdvanceEngine.hpp"

using namespace clockAdvance;

void ClockAdvanceEngine::updateState(float sampleRate, float sampleTime)
{
    _msSinceRisingEdge += sampleTime;
    bool trig = _trigger.process(controls->getClock());
    if (trig)
    {
        _clock.update(_msSinceRisingEdge);
        _msSinceRisingEdge = 0;
    }
}

void ClockAdvanceEngine::process(float sampleRate, float sampleTime) {
    updateState(sampleRate, sampleTime);
    if (_clock.goodBPM())
    {
        strBPM = std::to_string(_clock.getBPM());
    }
    else
    {
        strBPM = strInvalidState;
    }
}