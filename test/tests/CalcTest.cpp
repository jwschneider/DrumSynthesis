#include "CppUTest/TestHarness.h"
#include "../../src/Calculations.hpp"

TEST_GROUP(CalcTest)
{
    void setup()
    {

    }

    void teardown()
    {

    }
};

TEST(CalcTest, TestOne)
{
    float x = 3.1415;
    float expected = exp(x);
    float actual = ExpApprox<float, 16>::evaluate(x);
    DOUBLES_EQUAL(expected, actual, 0.1);
}