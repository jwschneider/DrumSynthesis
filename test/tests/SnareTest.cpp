#include "CppUTest/TestHarness.h"
#include "../test-src/testHarness.hpp"
#include "../../src/Snare/Snare.hpp"

using namespace snare;

TEST_GROUP(InitTests)
{
    SnareEngine *_engine;
    SnareControls *_controls;
    TestHarness *_harness;
    void setup()
    {
        _harness = new TestHarness(Snare::NUM_PARAMS, Snare::NUM_OUTPUTS, Snare::NUM_INPUTS, Snare::NUM_LIGHTS);
        _controls = new SnareControls(&_harness->params, &_harness->outputs, &_harness->inputs, &_harness->lights);
        _engine = new SnareEngine(_controls);
    }
    void teardown()
    {
        delete _harness;
        delete _engine;
    }
};

TEST(InitTests, Init)
{
    float sampleRate = 44100.f;
    float deltaT = 1.f / sampleRate;
    for (int i = 0; i < 3; i++)
        _engine->process(sampleRate, deltaT);
    CHECK(true);
}