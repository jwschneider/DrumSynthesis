#include "CppUTest/TestHarness.h"
#include "../test-src/testHarness.hpp"
#include "../../src/ClockAdvance/ClockAdvance.hpp"

using namespace clockAdvance;

TEST_GROUP(BPMClockTest)
{
    ClockAdvanceEngine *_engine;
    TestHarness *_harness;
    ClockAdvanceControls *_controls;
    void setup()
    {
        _harness = new TestHarness(ClockAdvance::NUM_PARAMS, ClockAdvance::NUM_OUTPUTS, ClockAdvance::NUM_INPUTS, ClockAdvance::NUM_LIGHTS);
        _controls = new ClockAdvanceControls(&_harness->params, &_harness->outputs, &_harness->inputs, &_harness->lights);
        _engine = new ClockAdvanceEngine(_controls);
    }
    void teardown()
    {
        delete _harness;
        delete _engine;
    }
};

TEST(BPMClockTest, GoodClockTest)
{
    float sampleRate = 44100.f;
    float trig = 0.f;
    float deltaT = 0.25f;
    for (float time = 0.f; time < 3.f; time += deltaT)
    {
        _harness->setInput(ClockAdvance::CLOCK_INPUT, trig);
        _engine->process(sampleRate, deltaT);
        trig = 1.f - trig;
    };
    STRCMP_EQUAL("120", _engine->strBPM.c_str());
}

TEST_GROUP(ParamTest)
{
    ClockAdvanceEngine *_engine;
    TestHarness *_harness;
    ClockAdvanceControls *_controls;
    void setup()
    {
        _harness = new TestHarness(ClockAdvance::NUM_PARAMS, ClockAdvance::NUM_OUTPUTS, ClockAdvance::NUM_INPUTS, ClockAdvance::NUM_LIGHTS);
        _controls = new ClockAdvanceControls(&_harness->params, &_harness->outputs, &_harness->inputs, &_harness->lights);
        _engine = new ClockAdvanceEngine(_controls);
    }
    void teardown()
    {
        delete _harness;
        delete _engine;
    }
};

TEST(ParamTest, InitTest)
{
    float sampleRate = 44100.f;
    float trig = 0.f;
    _harness->setParam(ClockAdvance::NOTESNUMERATOR_PARAM, 1.f);
    _harness->setParam(ClockAdvance::NOTESDENOMINATOR_PARAM, 3.f);
    _harness->setParam(ClockAdvance::SWITCH_PARAM, 0.f);
    float deltaT = 0.25f; // 120 BPM
    for (float time = 0.f; time < 3.f; time += deltaT)
    {
        _harness->setInput(ClockAdvance::CLOCK_INPUT, trig);
        _engine->process(sampleRate, deltaT);
        trig = 1.f - trig;    
    }
    STRCMP_EQUAL("120", _engine->strBPM.c_str());
    STRCMP_EQUAL("1", _engine->strNotesNum.c_str());
    STRCMP_EQUAL("8", _engine->strNotesDenom.c_str());
    STRCMP_EQUAL("250", _engine->strMS.c_str());
}

TEST(ParamTest, MSTest)
{
    float sampleRate = 44100.f;
    float trig = 0.f;
    _harness->setParam(ClockAdvance::MS_PARAM, 250.f);
    _harness->setParam(ClockAdvance::SWITCH_PARAM, 1.f);
    float deltaT = 0.25f; // 120 BPM
    for (float time = 0.f; time < 3.f; time += deltaT)
    {
        _harness->setInput(ClockAdvance::CLOCK_INPUT, trig);
        _engine->process(sampleRate, deltaT);
        trig = 1.f - trig;    
    }
    STRCMP_EQUAL("120", _engine->strBPM.c_str());
    STRCMP_EQUAL("1", _engine->strNotesNum.c_str());
    STRCMP_EQUAL("8", _engine->strNotesDenom.c_str());
    STRCMP_EQUAL("250", _engine->strMS.c_str());
}