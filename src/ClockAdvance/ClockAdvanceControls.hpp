#pragma once
#include "../common/ModuleControls.hpp"

namespace clockAdvance {
class ClockAdvanceControls : public ModuleControls {
    public:
    ClockAdvanceControls(vector<Param>* p, vector<Output>* o, vector<Input>* i, vector<Light>* l) : ModuleControls {p, o, i, l}
    {

    }
    ~ClockAdvanceControls()
    {

    }
    
};
}