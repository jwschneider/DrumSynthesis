#include "CppUTest/TestHarness.h"
#include "../../src/DecayEnvelope.hpp"

TEST_GROUP(DecayEnvelopeTest)
{
    DecayEnvelope *decay;
    void setup()
    {
        decay = new DecayEnvelope;
    }

    void teardown()
    {
        delete decay;
    }
};

TEST(DecayEnvelopeTest, test1)
{
    float tolerance = 0.001;
    const float maximumLevel = 1.f;
    const float minimumLevel = 0.0001;
    float sampleRate = 44100.f;
    float duration = 1.0;
    decay->init(duration, sampleRate);
    decay->process(sampleRate, duration / 2.f);
    float lambda = (1.f / duration) * (std::log(minimumLevel) - std::log(maximumLevel));
    float expected = std::exp(lambda * (duration / 2.f));
    DOUBLES_EQUAL(expected, decay->getValue(), tolerance);
    decay->process(sampleRate, duration / 2.f);
    expected = std::exp(lambda * duration);
    DOUBLES_EQUAL(expected, decay->getValue(), tolerance);
}

