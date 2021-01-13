#include "MyModule.hpp"

using namespace mymodule;

float mymodule::MyModuleControls::getPitch() { return getParam(MyModule::PITCH_PARAM);}
float mymodule::MyModuleControls::getInputVoltage() { return getInput(MyModule::PITCH_INPUT);}
void mymodule::MyModuleControls::setOutputVoltage(float v) { setOutput(MyModule::SINE_OUTPUT, v);}
void mymodule::MyModuleControls::setLightBrightness(float b) { setLight(MyModule::BLINK_LIGHT, b);}