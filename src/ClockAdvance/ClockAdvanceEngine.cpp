#include "ClockAdvanceEngine.hpp"

using namespace clockAdvance;

float notesToSeconds(int num, int denom, int BPM){
    if (BPM == 0)
    {
        return std::numeric_limits<float>::max();
    }
    return (((float) num / (float) denom) * 4 * 60) / (float) BPM;
}

void secondsToNotes(float advanceSec, float clockSec, int *num, int *denom)
{
    float notes = advanceSec / clockSec;
    uint32_t numerator = max((uint32_t) (notes * 128), (uint32_t) 1);
    uint32_t denominator = 128 * 4;
    while (!(numerator & 1))
    {
        numerator >>= 1;
        denominator >>= 1;
    }
    *num = numerator;
    *denom = denominator;
}

void ClockAdvanceEngine::updateNotes()
{
    _notesDenom = controls->getNotesDenominator();
    _notesNum = controls->getNotesNumerator() % _notesDenom;
}

void ClockAdvanceEngine::updateMS()
{
    _advanceSec = min(controls->getMS() / 1000.f, _clock.getSecPerBeat());
}

void ClockAdvanceEngine::updateState(float sampleRate, float sampleTime)
{
    _secSinceRisingEdge += sampleTime;
    bool trig = _trigger.process(controls->getClock());
    if (trig)
    {
        _clock.update(_secSinceRisingEdge);
        _secSinceRisingEdge = 0;
    }
}

void ClockAdvanceEngine::process(float sampleRate, float sampleTime) {
    updateState(sampleRate, sampleTime);
    updateNotes();
    updateMS();
    bool goodClk = _clock.goodBPM();
    if (goodClk)
    {
        if (controls->msMode())
        {
            secondsToNotes(_advanceSec, _clock.getSecPerBeat(), &_notesNum, &_notesDenom);
        }
        else
        {
            _advanceSec = min(notesToSeconds(_notesNum, _notesDenom, _clock.getBPM()), 0.999f);
        }
        _delaySec = _clock.getSecPerBeat() - _advanceSec;
        strBPM = std::to_string(_clock.getBPM());
        strMS = std::to_string((int)(_advanceSec * 1000));
        strNotesNum = std::to_string(_notesNum);
        strNotesDenom = std::to_string(_notesDenom);
    }
    else
    {
        strBPM = strInvalidState;
        strMS = controls->msMode() ? std::to_string((int)(_advanceSec * 1000)) : strInvalidState;
        strNotesNum = !controls->msMode() ? std::to_string(_notesNum) : strInvalidState;
        strNotesDenom = !controls->msMode() ? std::to_string(_notesDenom) : strInvalidState;
    }
}