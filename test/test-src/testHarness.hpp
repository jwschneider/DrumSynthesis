#include "../../src/common/ModuleControls.hpp"

class TestHarness {
    public:
        TestHarness() = default;        
        TestHarness(int numParams, int numOutputs, int numInputs, int numLights);
        ~TestHarness();
        void setParam(int param, float val);
        void setInput(int input, float val);
        float getLight(int light);
        float getOutput(float output);
        vector<Param> params;
        vector<Output> outputs;
        vector<Input> inputs;
        vector<Light> lights;
    private:
        void initMembers(int numParams, int numOutputs, int numInputs, int numLights);
        void destroyMembers();
};