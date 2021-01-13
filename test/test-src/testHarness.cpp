#include "testHarness.hpp"


TestHarness::TestHarness(int numParams, int numInputs, int numOutputs, int numLights)
{
    initMembers(numParams, numInputs, numOutputs, numLights);
}
TestHarness::~TestHarness()
{
    destroyMembers();
}

void TestHarness::setParam(int param, float val)
{
    params[param].setValue(val);
}
void TestHarness::setInput(int input, float val)
{
    inputs[input].setVoltage(val);
}
float TestHarness::getLight(int light)
{
    return lights[light].getBrightness();
}
float TestHarness::getOutput(float output)
{
    return outputs[output].getVoltage();
}

void TestHarness::initMembers(int numParams, int numInputs, int numOutputs, int numLights)
{
    params = vector<Param>(numParams);
    inputs = vector<Input>(numInputs);
    outputs = vector<Output>(numOutputs);
    lights = vector<Light>(numLights);
}

void TestHarness::destroyMembers()
{
    params.clear();
    inputs.clear();
    outputs.clear();
    lights.clear();
}
