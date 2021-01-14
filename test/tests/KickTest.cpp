#include "CppUTest/TestHarness.h"
#include "../test-src/testHarness.hpp"
#include "../../src/Kick/Kick.hpp"
#include "../../src/Kick/KickEngine.hpp"

using namespace kick;

TEST_GROUP(KickTest)
{
    KickEngine *_engine;
    TestHarness *_harness;  
    void setup()
    {
        _harness = new TestHarness(Kick::NUM_PARAMS, Kick::NUM_OUTPUTS, Kick::NUM_INPUTS, Kick::NUM_LIGHTS);
        KickControls *controls = new KickControls(&_harness->params, &_harness->outputs, &_harness->inputs, &_harness->lights);
        _engine = new KickEngine(controls);
    }
    void teardown()
    {
        delete _harness;
        delete _engine;
    }
};

TEST(KickTest, SecondTest)
{   

}