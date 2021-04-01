#pragma once
#include <engine/Module.hpp>
#include <app/ModuleWidget.hpp>
#include "SnareEngine.hpp"
#include "../plugin.hpp"

namespace snare {
class Snare : public Module {
    public:
    
    //std::string colors[] = {"white", "pink", "red", "violet", "blue", "grey"};
    enum ParamIds {
        BASEFQ_PARAM,
        BASEDECAY_PARAM,
        BASEAMP_PARAM,
        MOD0_PARAM,
        MOD1_PARAM,
        MOD2_PARAM,
        MOD3_PARAM,
        HARMONIC1_PARAM,
        HARMONIC2_PARAM,
        HARMONICSPACING_PARAM,
        HARMONICDECAY_PARAM,
        HARMONICAMP_PARAM,
        FMTONE_PARAM,
        FMCHARACTER_PARAM,
        FMDEPTH_PARAM,
        FMFEEDBACK_PARAM,
        FMAMP_PARAM,
        NOISECOLOR_PARAM,
        RINGMODULATION_PARAM,
        NOISEAMP_PARAM,
        VELOCITY_PARAM,
        SNAREDECAY_PARAM,
        SNAREAMP_PARAM,
        AUTONOTCH_PARAM,
        MASTERAMP_PARAM,
        NOTCH1_PARAM,
        NOTCH2_PARAM,
        NOTCH3_PARAM,
        LPF_PARAM,
        HPF_PARAM,
        NUM_PARAMS
    };
    enum InputIds {
        MOD0_INPUT,
        MOD1_INPUT,
        MOD2_INPUT,
        MOD3_INPUT,
        TRIGGER_INPUT,
        NUM_INPUTS
    };
    enum OutputIds {
        OUTPUT_OUTPUT,
        NUM_OUTPUTS
    };
    enum LightIds {
        NUM_LIGHTS
    };

    Snare();

    void process(const ProcessArgs& args) override;
    std::string colors[6] = {"white", "pink", "red", "violet", "blue", "grey"};
    private:
        SnareEngine *engine;
};

class SnarePanel : public ModuleWidget
{
    public:
    SnarePanel(Snare *snare);
};
}// namespace snare