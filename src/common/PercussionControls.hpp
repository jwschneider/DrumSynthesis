#pragma once
#include "ModuleControls.hpp"

class PercussionControls : public ModuleControls
{
    public:
    PercussionControls(vector<Param>* p, vector<Output>* o, vector<Input>* i, vector<Light>* l) : ModuleControls {p, o, i, l}
    {

    }
    ~PercussionControls()
    {

    }
    virtual void setOutputVoltage(float out) = 0;
    virtual float getTrigger() = 0;
    virtual float getLongestDecay() = 0;
};