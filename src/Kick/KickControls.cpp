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

void KickControls::setOutputVoltage(float val)
{
    this->setOutput(Kick::OUTPUT_OUTPUT, val);
}

float KickControls::getFundamentalFQ()
{
    float inputVoltage = this->getInput(Kick::LOW_FUNDAMENTAL_INPUT);
    float paramFQ = this->getParam(Kick::LOW_FUNDAMENTAL_PARAM);
    float ret = paramFQ * std::pow(2, inputVoltage);
    return clamp(ret, 10.f, 100.f);
}
float KickControls::getFQSpread()
{
    float inputVoltage = this->getInput(Kick::LOW_SPREAD_INPUT);
    float paramFQ = this->getParam(Kick::LOW_SPREAD_PARAM);
    float ret = paramFQ * std::pow(2, inputVoltage);
    return clamp(ret, 0.f, 90.f);
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
    float ret = 5.f * (this->getInput(Kick::LOW_LEVEL_INPUT)*(M_SQRT2/10.f) + this->getParam(Kick::LOW_LEVEL_PARAM));
    return clamp(ret, 0.f, 5 * M_SQRT2);
}
float KickControls::getLowDecay()
{
    float inputVoltage = this->getInput(Kick::LOW_DECAY_INPUT) * 2.f / 5.f; // [-5, 5] -> [-2, 2]
    float paramVoltage = this ->getParam(Kick::LOW_DECAY_PARAM);
    return std::pow(10, inputVoltage + paramVoltage);
}
float KickControls::getLongestDecay()
{
    return getLowDecay();
}
float KickControls::getTrigger()
{
    return this->getInput(Kick::TRIG_INPUT);
}