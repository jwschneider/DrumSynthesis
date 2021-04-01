#pragma once
#include "../common/ModuleControls.hpp"

namespace snare {
class SnareControls : public ModuleControls {
    public:
    SnareControls(vector<Param>* p, vector<Output>* o, vector<Input>* i, vector<Light>* l) : ModuleControls {p, o, i, l}
    {

    }
    ~SnareControls()
    {

    }
};
} //namespace snare