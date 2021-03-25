#include "ClockAdvanceControls.hpp"
#include "ClockAdvance.hpp"

using namespace clockAdvance;

float ClockAdvanceControls::getClock() 
{
    return this->getInput(ClockAdvance::CLOCK_INPUT);
}