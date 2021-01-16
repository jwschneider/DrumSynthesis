#include "CppUTest/TestHarness.h"
#include "../test-src/testHarness.hpp"
#include "../../src/Kick/Kick.hpp"
#include "../../src/Kick/KickEngine.hpp"

using namespace kick;
using namespace rack::dsp;

TEST_GROUP(KickTestControls)
{
    TestHarness *_harness;  
    KickControls *_controls;
    void setup()
    {
        _harness = new TestHarness(Kick::NUM_PARAMS, Kick::NUM_OUTPUTS, Kick::NUM_INPUTS, Kick::NUM_LIGHTS);
        _controls = new KickControls(&_harness->params, &_harness->outputs, &_harness->inputs, &_harness->lights);
        // float fundamental = 10.f;
        // float partials = 1.0;
        // float spread = 10.f;
        // float bend = 0.f;
        // float decay = 0.1f;
        // float level = 1.f;
        // _harness->setParam(Kick::LOW_FUNDAMENTAL_PARAM, fundamental);
        // _harness->setParam(Kick::LOW_PARTIALS_PARAM, partials);
        // _harness->setParam(Kick::LOW_SPREAD_INPUT, spread);
        // _harness->setParam(Kick::LOW_BEND_PARAM, bend);
        // _harness->setParam(Kick::LOW_DECAY_PARAM, decay);
        // _harness->setParam(Kick::LOW_LEVEL_PARAM, level);
        // _harness->setInput(Kick::TRIG_INPUT, 0.f);
    }
    void teardown()
    {
        delete _harness;
        delete _controls;
    }
};

TEST(KickTestControls, Fundamental)
{
    float fundamental = 10.f;
    _harness->setParam(Kick::LOW_FUNDAMENTAL_PARAM, fundamental);
    _harness->setInput(Kick::LOW_FUNDAMENTAL_INPUT, 0.f);
    CHECK_EQUAL(fundamental, _controls->getFundamentalFQ());
    float inputVoltage = 1; // one octave higher
    _harness->setInput(Kick::LOW_FUNDAMENTAL_INPUT, inputVoltage);
    CHECK_EQUAL(2 * fundamental, _controls->getFundamentalFQ());
}

TEST(KickTestControls, Partials)
{
    float partials = 1.3;
    _harness->setParam(Kick::LOW_PARTIALS_PARAM, partials);
    CHECK_EQUAL(floor(partials), _controls->getPartials());
    _harness->setInput(Kick::LOW_PARTIALS_INPUT, 10.f / 16.f);
    CHECK_EQUAL(2, _controls->getPartials());
}

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
        float decay = 0.1f;
        float level = 1.f;
        _harness->setParam(Kick::LOW_FUNDAMENTAL_PARAM, fundamental);
        _harness->setParam(Kick::LOW_PARTIALS_PARAM, partials);
        _harness->setParam(Kick::LOW_SPREAD_PARAM, spread);
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
    float tolerance = 0.01;
    _engine->process(sampleRate, 0); // trigger needs input to start at 0
    _harness->setInput(Kick::TRIG_INPUT, 1.0);
    _engine->process(sampleRate, 0);
    CHECK_EQUAL(1, _engine->lowOscillators.size());
    CHECK_EQUAL(10.f, _engine->lowOscillators[0]->getFrequency());
    CHECK_EQUAL(1.0, _engine->lowOscillators[0]->getMagnitude());
    _engine->process(sampleRate, 0.025f); // 1/4 cycle
    float expected = 1.f * 0.1 * 5; // osc.getIm * decay(0.025) * level
    DOUBLES_EQUAL(expected, _harness->getOutput(Kick::OUTPUT_OUTPUT), tolerance);
}

TEST(KickTestSimple, TestTwo)
{
    _harness->setInput(Kick::TRIG_INPUT, 1.0);
}

TEST_GROUP(PartialsAndBend)
{
    KickEngine *_engine;
    TestHarness *_harness;  
    void setup()
    {
        _harness = new TestHarness(Kick::NUM_PARAMS, Kick::NUM_OUTPUTS, Kick::NUM_INPUTS, Kick::NUM_LIGHTS);
        KickControls *controls = new KickControls(&_harness->params, &_harness->outputs, &_harness->inputs, &_harness->lights);
        _engine = new KickEngine(controls);
        float fundamental = 10.f;
        float partials = 3.5;
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