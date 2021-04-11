#include "CppUTest/TestHarness.h"
#include "../test-src/testHarness.hpp"
#include "../../src/Snare/Snare.hpp"
#include <jansson.h>

using namespace snare;
using namespace rack;

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
    CHECK_EQUAL(_controls, _engine->getControls());
    float sampleRate = 44100.f;
    float deltaT = 1.f / sampleRate;
    for (int i = 0; i < 3; i++)
        _engine->process(sampleRate, deltaT);
    CHECK(true);
}

TEST(InitTests, ModMatrix)
{
    for (int i = 0; i < SnareControls::MOD_MATRIX_ROWS; i++)
    {
        for (int j = 0; j < SnareControls::MOD_MATRIX_COLUMNS; j++)
        {
            CHECK_EQUAL(0, _controls->getModMatrixEntry(i, j));
        }
    }
    CHECK_EQUAL(0, _controls->getModMatrixRowCount(3));
    _controls->toggleModMatrixEntry(3, 0);
    CHECK_EQUAL(1, _controls->getModMatrixRowCount(3));
}