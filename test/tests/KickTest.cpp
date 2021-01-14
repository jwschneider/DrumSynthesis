#include "CppUTest/TestHarness.h"
#include "../test-src/testHarness.hpp"
#include "../../src/Kick/Kick.hpp"
#include "../../src/Kick/KickEngine.hpp"

using namespace kick;

TEST_GROUP(KickTestSimple)
{
    KickEngine *_engine;
    TestHarness *_harness;  
    void setup()
    {
        _harness = new TestHarness(Kick::NUM_PARAMS, Kick::NUM_OUTPUTS, Kick::NUM_INPUTS, Kick::NUM_LIGHTS);
        KickControls *controls = new KickControls(&_harness->params, &_harness->outputs, &_harness->inputs, &_harness->lights);
        _engine = new KickEngine(controls);
        float fundamental = 10.f;
        float partials = 1.0;
        float spread = 10.f;
        float bend = 0.f;
        float decay = 0.f;
        float level = 1.f;
        _harness->setParam(Kick::LOW_FUNDAMENTAL_PARAM, fundamental);
        _harness->setParam(Kick::LOW_PARTIALS_PARAM, partials);
        _harness->setParam(Kick::LOW_SPREAD_INPUT, spread);
        _harness->setParam(Kick::LOW_BEND_PARAM, bend);
        _harness->setParam(Kick::LOW_DECAY_PARAM, decay);
        _harness->setParam(Kick::LOW_LEVEL_PARAM, level);
        _harness->setInput(Kick::TRIG_INPUT, 0.f);
    }
    void teardown()
    {
        delete _harness;
        delete _engine;
    }
};

TEST(KickTestSimple, TestOne)
{
    float sampleRate = 44100.f;
    _engine->process(sampleRate, 0); // trigger needs input to start at 0
    _harness->setInput(Kick::TRIG_INPUT, 1.0);
    _engine->process(sampleRate, 0);
    CHECK_EQUAL(1, _engine->lowOscillators.size());
    CHECK_EQUAL(10.f, _engine->lowOscillators[0]->getFrequency());
    CHECK_EQUAL(1.0, _engine->lowOscillators[0]->getMagnitude());
}