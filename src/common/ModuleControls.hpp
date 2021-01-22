#pragma once
#include <engine/Param.hpp>
#include <engine/Port.hpp>
#include <engine/Light.hpp>
#include <engine/ParamQuantity.hpp>
#include <vector>

using namespace rack::engine;
using namespace std;

class ModuleControls {
    public:
        ModuleControls() = default;
        ModuleControls(vector<Param>* p, vector<Output>* o, vector<Input>* i, vector<Light>* l)
        {
            params = p;
            outputs = o;
            inputs = i;
            lights = l;
        }
        virtual ~ModuleControls() {};
        float getParam(int param) {return (*params)[param].getValue();}
        float getInput(int input) {return (*inputs)[input].getVoltage();}
        void setOutput(int output, float val) {(*outputs)[output].setVoltage(val);}
        void setLight(int light, float val) {(*lights)[light].setBrightness(val);}
    private:
        vector<Param> *params;
        vector<Output> *outputs;
        vector<Input> *inputs;
        vector<Light> *lights;
};