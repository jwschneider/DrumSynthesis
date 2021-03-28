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

    // Gets the value of the CLK Input port
    float getClock();
    //
    int getNotesNumerator();
    // Must be >= 1
    int getNotesDenominator();
    // Must be > 0
    float getMS();
    // 0 == fraction mode; 1 == MS mode
    bool msMode();
    // Set Output 
    void setTriggerOutput(float val);
};
}