#include "CppUTest/TestHarness.h"
#include <vector>

extern "C"
{
	/*
	 * Add your c-only include files here
	 */
}

TEST_GROUP(MyCode)
{
    std::vector<int> *vec;
    void setup()
    {
        vec = new std::vector<int>();
    }

    void teardown()
    {
        delete vec;
    }
};

TEST(MyCode, test1)
{
    vec->push_back(1);
    CHECK_EQUAL(1, vec->back());
    /*
     * Instantiate your class, or call the function, you want to test.
     * Then delete this comment
     */
}

