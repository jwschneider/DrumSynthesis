#include "CppUTest/TestHarness.h"
#include "../../src/MyModule/MyModuleEngine.hpp"
#include "../test-src/testHarness.hpp"
#include "../../src/MyModule/MyModule.hpp"

using namespace mymodule;




TEST_GROUP(MyModuleTest)
{
    MyModuleEngine *_engine;
    TestHarness *_harness;
    MyModuleControls *_controls;
    void setup()
    {
        _harness = new TestHarness(MyModule::NUM_PARAMS, MyModule::NUM_OUTPUTS, MyModule::NUM_INPUTS, MyModule::NUM_LIGHTS);
        _controls = new MyModuleControls(&_harness->params, &_harness->outputs, &_harness->inputs, &_harness->lights);
        _engine = new MyModuleEngine(_controls);
    }
    void teardown()
    {
        delete _harness;
        delete _engine;
    }
};

TEST(MyModuleTest, ParamTest)
{   
    float tolerance = 0.001;
    _harness->setParam(MyModule::PITCH_PARAM, -1.f);
    float C_3 = 130.81;
    _engine->process(0, 1/(4*C_3));
    DOUBLES_EQUAL(5.f, _harness->getOutput(MyModule::SINE_OUTPUT), tolerance); // pi/2
    _engine->process(0, 1/(4*C_3));
    DOUBLES_EQUAL(0.f, _harness->getOutput(MyModule::SINE_OUTPUT), tolerance); // pi/
    _engine->process(0, 1/(4*C_3));
    DOUBLES_EQUAL(-5.f, _harness->getOutput(MyModule::SINE_OUTPUT), tolerance); // 3pi/2
    _engine->process(0, 1/(4*C_3));
    DOUBLES_EQUAL(0.f, _harness->getOutput(MyModule::SINE_OUTPUT), tolerance); // 2pi
};

TEST(MyModuleTest, InputTest)
{   
    float tolerance = 0.001;
    _harness->setInput(MyModule::PITCH_INPUT, -1.f);
    float C_3 = 130.81;
    _engine->process(0, 1/(4*C_3));
    DOUBLES_EQUAL(5.f, _harness->getOutput(MyModule::SINE_OUTPUT), tolerance); // pi/2
    _engine->process(0, 1/(4*C_3));
    DOUBLES_EQUAL(0.f, _harness->getOutput(MyModule::SINE_OUTPUT), tolerance); // pi/
    _engine->process(0, 1/(4*C_3));
    DOUBLES_EQUAL(-5.f, _harness->getOutput(MyModule::SINE_OUTPUT), tolerance); // 3pi/2
    _engine->process(0, 1/(4*C_3));
    DOUBLES_EQUAL(0.f, _harness->getOutput(MyModule::SINE_OUTPUT), tolerance); // 2pi
};

TEST(MyModuleTest, ParamAndInputTest)
{   
    float tolerance = 0.001;
    _harness->setParam(MyModule::PITCH_PARAM, -1.f);
    _harness->setInput(MyModule::PITCH_INPUT, -1.f);
    float C_2 = 65.406;
    _engine->process(0, 1/(4*C_2));
    DOUBLES_EQUAL(5.f, _harness->getOutput(MyModule::SINE_OUTPUT), tolerance); // pi/2
    _engine->process(0, 1/(4*C_2));
    DOUBLES_EQUAL(0.f, _harness->getOutput(MyModule::SINE_OUTPUT), tolerance); // pi/
    _engine->process(0, 1/(4*C_2));
    DOUBLES_EQUAL(-5.f, _harness->getOutput(MyModule::SINE_OUTPUT), tolerance); // 3pi/2
    _engine->process(0, 1/(4*C_2));
    DOUBLES_EQUAL(0.f, _harness->getOutput(MyModule::SINE_OUTPUT), tolerance); // 2pi
};
