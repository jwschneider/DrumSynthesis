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
    float partials = 1.5;
    _harness->setParam(Kick::LOW_PARTIALS_PARAM, partials);
    CHECK_EQUAL(floor(partials), _controls->getPartials());
    _harness->setInput(Kick::LOW_PARTIALS_INPUT, 15.f / 16.f);
    CHECK_EQUAL(2, _controls->getPartials());
}

TEST(KickTestControls, Spread)
{
    float spread = 10.f;
    _harness->setParam(Kick::LOW_SPREAD_PARAM, spread);
    CHECK_EQUAL(spread, _controls->getFQSpread());
    _harness->setInput(Kick::LOW_SPREAD_INPUT, 1.f); // one octave higher
    CHECK_EQUAL(2*spread, _controls->getFQSpread());
}

TEST(KickTestControls, Decay)
{
    float decay = -1.f;
    _harness->setParam(Kick::LOW_DECAY_PARAM, decay);
    DOUBLES_EQUAL(0.1, _controls->getLowDecay(), 0.001);
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
        float decay = -1.f;
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
    float expected = 1.f * 0.1f * 4 * 5; // osc.getIm * decay(0.025) * makeup gain * level
    DOUBLES_EQUAL(expected, _harness->getOutput(Kick::OUTPUT_OUTPUT), tolerance);
}

TEST(KickTestSimple, RetriggerTest)
{
    float sampleRate = 44100.f;
    float tolerance = 0.01;
    _engine->process(sampleRate, 0); // trigger needs input to start at 0
    _harness->setInput(Kick::TRIG_INPUT, 1.0);
    _engine->process(sampleRate, 0);
    _harness->setInput(Kick::TRIG_INPUT, 0.0);
    _engine->process(sampleRate, 0.025f); // 1/4 cycle
    float expected = 1.f * 0.1f * 4 * 5; // osc.getIm * decay(0.025) * makeup gain * level
    DOUBLES_EQUAL(expected, _harness->getOutput(Kick::OUTPUT_OUTPUT), tolerance);
    _harness->setInput(Kick::TRIG_INPUT, 1.0);
    _engine->process(sampleRate, 0.025f);
    expected = 1.f * 0.1f * 4 * 5;
    DOUBLES_EQUAL(expected, _harness->getOutput(Kick::OUTPUT_OUTPUT), tolerance);
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
        float bend = 0.5f;
        float decay = -1.f;
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

TEST(PartialsAndBend, TestOne)
{    
    float sampleRate = 44100.f;
    float tolerance = 0.001;
    _engine->process(sampleRate, 0); // trigger needs input to start at 0
    _harness->setInput(Kick::TRIG_INPUT, 1.0);
    _engine->process(sampleRate, 0);
    CHECK_EQUAL(3, _engine->lowOscillators.size());
    DOUBLES_EQUAL(10.f, _engine->lowOscillators[0]->getFrequency(), tolerance);
    DOUBLES_EQUAL(1.f / 2.207106, _engine->lowOscillators[0]->getMagnitude(), tolerance);
    DOUBLES_EQUAL(20.f, _engine->lowOscillators[1]->getFrequency(), tolerance);
    DOUBLES_EQUAL(0.707106 / 2.207106, _engine->lowOscillators[1]->getMagnitude(), tolerance);
    DOUBLES_EQUAL(30.f, _engine->lowOscillators[2]->getFrequency(), tolerance);
    DOUBLES_EQUAL(0.5 / 2.207106, _engine->lowOscillators[2]->getMagnitude(), tolerance);
}

TEST_GROUP(KickTestDefault)
{
    KickEngine *_engine;
    TestHarness *_harness;  
    void setup()
    {
        _harness = new TestHarness(Kick::NUM_PARAMS, Kick::NUM_OUTPUTS, Kick::NUM_INPUTS, Kick::NUM_LIGHTS);
        KickControls *controls = new KickControls(&_harness->params, &_harness->outputs, &_harness->inputs, &_harness->lights);
        _engine = new KickEngine(controls);
        float fundamental = 30.f;
        float partials = 8;
        float spread = 45.f;
        float bend = 0.5f;
        float decay = -1.f;
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

// TEST(KickTestDefault, BoundedOutputVoltage)
// {
//     float sampleRate = 44100.f;
//     float secondsPerSample = 1.f / sampleRate;
//     //float tolerance = 0.001;
//     _engine->process(sampleRate, 0); // trigger needs input to start at 0
//     _harness->setInput(Kick::TRIG_INPUT, 1.0);
//     _engine->process(sampleRate, 0);
//     for (float i = 0.f; i < 1.0; i += secondsPerSample)
//     {
//         _engine->process(sampleRate, secondsPerSample);
//         float output = _harness->getOutput(Kick::OUTPUT_OUTPUT);
//         CHECK_TEXT((output <= 10.f) && (output >= -10.f), "Output voltage is out of bounds [-10, 10]");
//     }
// }

TEST_GROUP(MidTest)
{
        KickEngine *_engine;
    TestHarness *_harness;  
    void setup()
    {
        _harness = new TestHarness(Kick::NUM_PARAMS, Kick::NUM_OUTPUTS, Kick::NUM_INPUTS, Kick::NUM_LIGHTS);
        KickControls *controls = new KickControls(&_harness->params, &_harness->outputs, &_harness->inputs, &_harness->lights);
        _engine = new KickEngine(controls);

        float tone = -1.f;
        float character = 0.f;
        float lp = 0.f;
        float hp = -1.f;
        float decay = -1.f;
        float level = 1.f;
        _harness->setParam(Kick::MID_TONE_PARAM, tone);
        _harness->setParam(Kick::MID_CHARACTER_PARAM, character);
        _harness->setParam(Kick::MID_LP_PARAM, lp);
        _harness->setParam(Kick::MID_HP_PARAM, hp);
        _harness->setParam(Kick::MID_DECAY_PARAM, decay);
        _harness->setParam(Kick::MID_LEVEL_PARAM, level); 
    }
    void teardown()
    {
        delete _harness;
        delete _engine;
    }
};

TEST(MidTest, AntiClickTest)
{
    float sampleRate = 44100.f;
    float secondsPerSample = 1.f / sampleRate;
    float tolerance = 0.1;
    _harness->setInput(Kick::TRIG_INPUT, 0.f);
    _engine->process(sampleRate, 0); // trigger needs input to start at 0
    _harness->setInput(Kick::TRIG_INPUT, 1.0);
    _engine->process(sampleRate, 0);
    _harness->setInput(Kick::TRIG_INPUT, 0.f);
    float currentValue = _harness->getOutput(Kick::OUTPUT_OUTPUT);
    for (float i = 0.f; i < 0.5; i += secondsPerSample)
    {
        _engine->process(sampleRate, secondsPerSample);
        CHECK_TEXT(abs(currentValue - _harness->getOutput(Kick::OUTPUT_OUTPUT)) < tolerance, "Discontinuity between samples > 0.1V first trigger");
        currentValue = _harness->getOutput(Kick::OUTPUT_OUTPUT);
    }
    _harness->setInput(Kick::TRIG_INPUT, 1.0);
    for (float i = 0.f; i < 0.5; i += secondsPerSample)
    {
        _engine->process(sampleRate, secondsPerSample);
        CHECK_TEXT(abs(currentValue - _harness->getOutput(Kick::OUTPUT_OUTPUT)) < tolerance, "Discontinuity between samples > 0.1V second trigger");
        currentValue = _harness->getOutput(Kick::OUTPUT_OUTPUT);
    }
}

TEST(MidTest, ModIndexTest)
{
    float sampleRate = 44100.f;
    float tolerance = 0.01;
    _harness->setInput(Kick::TRIG_INPUT, 0.f);
    _engine->process(sampleRate, 0); // trigger needs input to start at 0
    _harness->setInput(Kick::TRIG_INPUT, 1.0);
    _engine->process(sampleRate, 0);
    CHECK_EQUAL(440.f, _engine->midOscillator.getModFQ());
    DOUBLES_EQUAL(0.08f, _engine->midOscillator.getModIndex(), tolerance);
    _engine->process(sampleRate, 1.f/(4* _engine->midOscillator.getModFQ()));
    DOUBLES_EQUAL(8.f, _engine->midOscillator.getModIndex(), tolerance);
    _engine->process(sampleRate, 0.2f / 3.f);
    DOUBLES_EQUAL(4.f, _engine->midOscillator.getModIndex(), tolerance);
}