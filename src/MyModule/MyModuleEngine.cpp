#include "MyModuleEngine.hpp"
#include <dsp/common.hpp>
#include <math.h>
#include <math.hpp>

using namespace mymodule;
using namespace rack::dsp;
using namespace rack::math;

void mymodule::MyModuleEngine::process(float sampleRate, float sampleTime)
{
    // rewrite example process() to use only function calls to MyModuleControls
    float pitch = controls->getPitch();
    pitch += controls->getInputVoltage();
    pitch = clamp(pitch, -4.f, 4.f);
    float freq = FREQ_C4 * std::pow(2.f, pitch);
    // Accumulate the phase
    phase += freq * sampleTime;
    if (phase >= 0.5f)
        phase -= 1.f;
    float sine = std::sin(2.f * M_PI * phase);
    controls->setOutputVoltage(5.f*sine);
    blinkPhase += sampleTime;
    if (blinkPhase >= 1.f)
        blinkPhase -= 1.f;
    controls->setLightBrightness(blinkPhase < 0.5f ? 1.f : 0.f);

}
