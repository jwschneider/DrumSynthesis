#include "CppUTest/TestHarness.h"
#include "../../src/common/SimpleOscillator.hpp"

#include <cmath>
#include <iostream>

TEST_GROUP(SimpleOscTest)
{
    SimpleOscillator *osc;
    void setup()
    {
        osc = new SimpleOscillator;
    }

    void teardown()
    {
        delete osc;
    }
};

TEST(SimpleOscTest, test1)
{
    float C_3 = 130.81;
    float tolerance = 0.001;
    osc->setFrequency(C_3);
    osc->setMagnitude(2);
    osc->process(0, 1/(4*C_3));
    DOUBLES_EQUAL(2, osc->getImaginary(), tolerance); // pi/2
    osc->process(0, 1/(4*C_3));
    DOUBLES_EQUAL(0, osc->getImaginary(), tolerance); // pi
    osc->process(0, 1/(4*C_3));
    DOUBLES_EQUAL(-2, osc->getImaginary(), tolerance); // 3pi/2
    osc->process(0, 1/(4*C_3));
    DOUBLES_EQUAL(0, osc->getImaginary(), tolerance); // 2pi
}

TEST(SimpleOscTest, oneCycle)
{
    float C_3 = 130.81;
    float tolerance = 0.01;
    float sampleRate = 88200.f;
    float tickSampleTime = 1.f / sampleRate;
    osc->setFrequency(C_3);
    for (float time = 0.f; time < 1.f / C_3; time += tickSampleTime)
    {
        osc->process(sampleRate, tickSampleTime);
    }
    float expected = 0; // one cycle
    DOUBLES_EQUAL(expected, osc->getImaginary(), tolerance);
}

TEST(SimpleOscTest, oneSecond)
{
    float C_3 = 130.81;
    float tolerance = 0.01;
    float sampleRate = 65536;
    float sampleTime = 1.f / sampleRate;
    osc->setFrequency(C_3);
    for (float i = 0.f; i < 1; i += sampleTime)
    {
        osc->process(sampleRate, sampleTime);
    }
    float expected = std::sin(2 * M_PI * C_3 / 1.f);
    DOUBLES_EQUAL(expected, osc->getImaginary(), tolerance);
}
