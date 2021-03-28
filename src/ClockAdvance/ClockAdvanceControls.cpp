#include "ClockAdvanceControls.hpp"
#include "ClockAdvance.hpp"

using namespace clockAdvance;

float ClockAdvanceControls::getClock() 
{
    return this->getInput(ClockAdvance::CLOCK_INPUT);
}


int ClockAdvanceControls::getNotesNumerator()
{
    return this->getParam(ClockAdvance::NOTESNUMERATOR_PARAM);
}
int ClockAdvanceControls::getNotesDenominator()
{
    return 1 << (int) this->getParam(ClockAdvance::NOTESDENOMINATOR_PARAM);
}
// Must be > 0
float ClockAdvanceControls::getMS()
{
    return max((int)this->getParam(ClockAdvance::MS_PARAM), 0);
}
// 0 == fraction mode; 1 == MS mode
bool ClockAdvanceControls::msMode()
{
    return (int) this->getParam(ClockAdvance::SWITCH_PARAM);
}