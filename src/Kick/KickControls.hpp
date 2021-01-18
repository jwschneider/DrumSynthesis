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
    // FS = C_4 * 2^(Vp + Vi)
    float getFQSpread();
    // Get Bend in [0.01, 1] unitless
    float getBend();
    // Gets number of partials to include in [0, 16]
    int getPartials();
    // Gets amplitude in [0, 5*sqrt(2)]
    float getLowLevel();
    // Gets low FQ decay time in [0.01, 1]s
    // D = 10^(Vi + Vp) where Vp [-2, 0] and Vi [-2, 2]
    float getLowDecay();
    // Gets longest of the three decay elements in [0.01, 1]s
    float getLongestDecay();
    // Gets trigger
    float getTrigger();
    // Mid Tone FQ in [440, 1760] Hz
    float getMidTone();
    // Mid Character FQ in [440, 1760] Hz
    float getMidCharacter();
    // Mid LP Frequency
    float getMidLP();
    // Mid HP Frequency
    float getMidHP();
    // D = 10^(Vi + Vp) where Vp [-2, 0] and Vi [-2, 2]
    float getMidDecay();
    // Gets amplitude in [0, 5*sqrt(2)]
    float getMidLevel();
};
} //namespace Kick