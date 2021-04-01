#include "Snare.hpp"

using namespace snare;

Snare::Snare() {
	config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
	configParam(BASEFQ_PARAM, -5.f, 5.f, 0.f, "Drum Base Frequency", "Hz", 2, dsp::FREQ_A4);
	configParam(BASEDECAY_PARAM, 0.f, 1.f, 0.f, "");
	configParam(BASEAMP_PARAM, 0.f, 1.f, 0.f, "");
	configParam(MOD0_PARAM, 0.f, 1.f, 0.f, "");
	configParam(MOD1_PARAM, 0.f, 1.f, 0.f, "");
	configParam(MOD2_PARAM, 0.f, 1.f, 0.f, "");
	configParam(MOD3_PARAM, 0.f, 1.f, 0.f, "");
	configParam(HARMONIC1_PARAM, 0.f, 1.f, 0.f, "");
	configParam(HARMONIC2_PARAM, 0.f, 1.f, 0.f, "");
	configParam(HARMONICSPACING_PARAM, 0.f, 1.f, 0.f, "");
	configParam(HARMONICDECAY_PARAM, 0.f, 1.f, 0.f, "");
	configParam(HARMONICAMP_PARAM, 0.f, 1.f, 0.f, "");
	configParam(FMTONE_PARAM, 0.f, 1.f, 0.f, "");
	configParam(FMCHARACTER_PARAM, 0.f, 1.f, 0.f, "");
	configParam(FMDEPTH_PARAM, 0.f, 1.f, 0.f, "");
	configParam(FMFEEDBACK_PARAM, 0.f, 1.f, 0.f, "");
	configParam(FMAMP_PARAM, 0.f, 1.f, 0.f, "");
	configParam(NOISECOLOR_PARAM, 0.f, 1.f, 0.f, "");
	configParam(RINGMODULATION_PARAM, 0.f, 1.f, 0.f, "");
	configParam(NOISEAMP_PARAM, 0.f, 1.f, 0.f, "");
	configParam(VELOCITY_PARAM, 0.f, 1.f, 0.f, "");
	configParam(SNAREDECAY_PARAM, 0.f, 1.f, 0.f, "");
	configParam(SNAREAMP_PARAM, 0.f, 1.f, 0.f, "");
	configParam(AUTONOTCH_PARAM, 0.f, 1.f, 0.f, "");
	configParam(MASTERAMP_PARAM, 0.f, 1.f, 0.f, "");
	configParam(NOTCH1_PARAM, 0.f, 1.f, 0.f, "");
	configParam(NOTCH2_PARAM, 0.f, 1.f, 0.f, "");
	configParam(NOTCH3_PARAM, 0.f, 1.f, 0.f, "");
	configParam(LPF_PARAM, 0.f, 1.f, 0.f, "");
	configParam(HPF_PARAM, 0.f, 1.f, 0.f, "");

	SnareControls *controls = new SnareControls(&params, &outputs, &inputs, &lights);
	engine = new SnareEngine(controls);
}
void Snare::process(const ProcessArgs& args) {
	engine->process(args.sampleRate, args.sampleTime);
}

//Model* modelSnare = createModel<Snare, SnareWidget>("Snare");