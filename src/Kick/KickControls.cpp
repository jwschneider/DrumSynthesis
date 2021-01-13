#include "KickControls.hpp"
#include "Kick.hpp"
#include <dsp/common.hpp>
#include <math.hpp>

using namespace kick;
using namespace rack::dsp;
using namespace math;

inline float VoltageToFrequency(float volts)
{
    return FREQ_C4 * std::pow(2, volts);
}

const float sqrt2 = 1.41421356237309504880;

void KickControls::setOutputVoltage(float val)
{
    this->setOutput(Kick::OUTPUT_OUTPUT, val);
}

float KickControls::getFundamentalFQ()
{
    float intputVoltage = this->getInput(Kick::LOW_FUNDAMENTAL_INPUT);
    float inputFQ = VoltageToFrequency(intputVoltage);
    inputFQ = clamp(inputFQ, 10.f, 50.f);
    float paramFQ = this->getParam(Kick::LOW_FUNDAMENTAL_PARAM);
    return inputFQ + paramFQ;
}
float KickControls::getFQSpread()
{
    float inputVoltage = this->getInput(Kick::LOW_SPREAD_INPUT);
    float inputFQ = VoltageToFrequency(inputVoltage);
    inputFQ = clamp(inputFQ, 0.f, 90.f);
    float paramFQ = this->getParam(Kick::LOW_SPREAD_PARAM);
    return inputFQ + paramFQ;
}
float KickControls::getBend()
{
    float inputBend = this->getInput(Kick::LOW_BEND_INPUT) / 5.f;
    float paramBend = this->getParam(Kick::LOW_BEND_PARAM);
    return inputBend + paramBend;
}
// TODO make this knob only have a discrete set of integer choices
int KickControls::getPartials()
{
    int inputPartials = std::floor(this->getInput(Kick::LOW_PARTIALS_INPUT) * 1.6);
    int paramPartials = std::floor(this->getParam(Kick::LOW_PARTIALS_PARAM));
    return clamp(inputPartials + paramPartials, 0, 16);
}
float KickControls::getLevel()
{
    return (this->getInput(Kick::LOW_LEVEL_INPUT)*(sqrt2/10.f) + this->getParam(Kick::LOW_LEVEL_PARAM)) / 2.f;
}
float KickControls::getLowDecay()
{
    float inputVoltage = this->getInput(Kick::LOW_DECAY_INPUT);
    float inputSeconds = std::pow(2, inputVoltage / 5.f - 2.f);
    float paramVoltage = this ->getParam(Kick::LOW_DECAY_PARAM);
    float paramSeconds = std::pow(2, paramVoltage);
    return inputSeconds + paramSeconds;
}
float KickControls::getLongestDecay()
{
    return getLowDecay();
}
float KickControls::getTrigger()
{
    return this->getInput(Kick::TRIG_INPUT);
}