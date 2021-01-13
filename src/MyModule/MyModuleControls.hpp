#pragma once
#include "../ModuleControls.hpp"

namespace mymodule
{
    class MyModuleControls : public ModuleControls {
        public:
            MyModuleControls(vector<Param>* p, vector<Output>* o, vector<Input>* i, vector<Light>* l, vector<ParamQuantity*>* pq) : ModuleControls {p, o, i, l, pq}
            {

            }
            float getPitch();
            float getInputVoltage();
            void setOutputVoltage(float v);
            void setLightBrightness(float b);
    };
};