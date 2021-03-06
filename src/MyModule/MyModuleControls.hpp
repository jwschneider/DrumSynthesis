#pragma once
#include "../common/ModuleControls.hpp"

namespace mymodule
{
    class MyModuleControls : public ModuleControls {
        public:
            MyModuleControls(vector<Param>* p, vector<Output>* o, vector<Input>* i, vector<Light>* l) : ModuleControls {p, o, i, l}
            {

            }
            ~MyModuleControls()
            {

            }
            float getPitch();
            float getInputVoltage();
            void setOutputVoltage(float v);
            void setLightBrightness(float b);
    };
};