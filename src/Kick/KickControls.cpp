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
    float inputBend = this->getInput(Kick::LOW_BEND_INPUT) / 10.f;
    float paramBend = this->getParam(Kick::LOW_BEND_PARAM);
    return clamp(inputBend + paramBend, 0.01, 1.f);
}
// TODO make this knob only have a discrete set of integer choices
int KickControls::getPartials()
{
    int inputPartials = std::floor(this->getInput(Kick::LOW_PARTIALS_INPUT) * 1.6);
    int paramPartials = std::floor(this->getParam(Kick::LOW_PARTIALS_PARAM));
    return clamp(inputPartials + paramPartials, 0, 16);
}
float KickControls::getLowLevel()
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
    return std::max(getLowDecay(), getMidDecay());
}
float KickControls::getTrigger()
{
    return this->getInput(Kick::TRIG_INPUT);
}

float KickControls::getMidTone()
{
    float paramVoltage = this->getParam(Kick::MID_TONE_PARAM);
    float inputVoltage = this->getInput(Kick::MID_TONE_INPUT) / 5.f;
    return FREQ_A4 * std::pow(2, paramVoltage + inputVoltage);
}

float KickControls::getMidToneVoltage()
{
    float paramVoltage = this->getParam(Kick::MID_TONE_PARAM);
    float inputVoltage = this->getInput(Kick::MID_TONE_INPUT);
    return paramVoltage + inputVoltage;
}

float KickControls::getMidCharacter()
{
    float paramVoltage = this->getParam(Kick::MID_CHARACTER_PARAM);
    float inputVoltage = this->getInput(Kick::MID_CHARACTER_INPUT) / 5.f;
    return FREQ_A4 * std::pow(2, paramVoltage + inputVoltage);
}
float KickControls::getMidLP()
{
    float paramVoltage = this->getParam(Kick::MID_LP_PARAM);
    float inputVoltage = this->getInput(Kick::MID_LP_INPUT);
    return FREQ_C4 * std::pow(2, paramVoltage + inputVoltage);
}
float KickControls::getMidHP()
{
    float paramVoltage = this->getParam(Kick::MID_HP_PARAM);
    float inputVoltage = this->getInput(Kick::MID_HP_INPUT);
    return FREQ_C4 * std::pow(2, paramVoltage + inputVoltage);
}
float KickControls::getMidDecay()
{
    float inputVoltage = this->getInput(Kick::MID_DECAY_INPUT) * 2.f / 5.f; // [-5, 5] -> [-2, 2]
    float paramVoltage = this ->getParam(Kick::MID_DECAY_PARAM);
    return std::pow(10, inputVoltage + paramVoltage);
}
float KickControls::getMidLevel()
{
    float ret = 5.f * (this->getInput(Kick::MID_LEVEL_INPUT)*(M_SQRT2/10.f) + this->getParam(Kick::MID_LEVEL_PARAM));
    return clamp(ret, 0.f, 5 * M_SQRT2);
}
float KickControls::getHeadTone()
{
    float paramVoltage = this->getParam(Kick::HEAD_TONE_PARAM);
    float inputVoltage = this->getInput(Kick::HEAD_TONE_INPUT) / 5.f;
    return FREQ_A4 * std::pow(2, paramVoltage + inputVoltage);
}
float KickControls::getHeadCharacter()
{
    float paramVoltage = this->getParam(Kick::HEAD_CHARACTER_PARAM);
    float inputVoltage = this->getInput(Kick::HEAD_CHARACTER_INPUT) / 5.f;
    return FREQ_A4 * std::pow(2, paramVoltage + inputVoltage);
}
float KickControls::getHeadLP()
{
    float paramVoltage = this->getParam(Kick::HEAD_LP_PARAM);
    float inputVoltage = this->getInput(Kick::HEAD_LP_INPUT);
    return FREQ_C4 * std::pow(2, paramVoltage + inputVoltage);
}
float KickControls::getHeadHP()
{
    float paramVoltage = this->getParam(Kick::HEAD_HP_PARAM);
    float inputVoltage = this->getInput(Kick::HEAD_HP_INPUT);
    return FREQ_C4 * std::pow(2, paramVoltage + inputVoltage);
}
float KickControls::getHeadDecay()
{
    float inputVoltage = this->getInput(Kick::HEAD_DECAY_INPUT) * 2.f / 5.f; // [-5, 5] -> [-2, 2]
    float paramVoltage = this ->getParam(Kick::HEAD_DECAY_PARAM);
    return std::pow(10, inputVoltage + paramVoltage);
}
float KickControls::getHeadLevel()
{
    float ret = 5.f * (this->getInput(Kick::HEAD_LEVEL_INPUT)*(M_SQRT2/10.f) + this->getParam(Kick::HEAD_LEVEL_PARAM));
    return clamp(ret, 0.f, 5 * M_SQRT2);
}