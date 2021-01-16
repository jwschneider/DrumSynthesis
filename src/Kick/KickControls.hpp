#pragma once
#include "../ModuleControls.hpp"

namespace kick {
class KickControls : public ModuleControls {
    public:
    KickControls(vector<Param>* p, vector<Output>* o, vector<Input>* i, vector<Light>* l) : ModuleControls {p, o, i, l}
    {

    }
    ~KickControls()
    {

    }
    void setOutputVoltage(float val);
    
    // Fundamental frequency in [10, 100] Hz
    // FQ = C_4 * 2^(Vp + Vi)
    float getFundamentalFQ();
    // Frequency spread in [0, 90] Hz
    float getFQSpread();
    // Get Bend in [-1, 1] unitless
    float getBend();
    // Gets number of partials to include in [0, 16]
    int getPartials();
    // Gets amplitude in [0, 5*sqrt(2)]
    float getLevel();
    // Gets low FQ decay time in [0.01, 1]s
    float getLowDecay();
    // Gets longest of the three decay elements in [0.01, 1]s
    float getLongestDecay();
    // Gets trigger
    float getTrigger();
};
} //namespace Kick