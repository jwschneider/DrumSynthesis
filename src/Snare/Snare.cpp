#include "Snare.hpp"

using namespace snare;

Snare::Snare() {
	config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
	configParam(BASEFQ_PARAM, -3.28950661719f, 0.71049338281f, -1.28950661719f, "Drum Base Frequency", "Hz", 2, dsp::FREQ_A4);
	configParam(BASEDECAY_PARAM, -2.f, 0.f, -1.f, "Base Decay Time", "s", 10.f, 1.f);
	configParam(BASEAMP_PARAM, 0.f, 1.f, 0.5f, "Base Amplitude Gain", "db", -10.f, 40.f);
	configParam(MOD0_PARAM, -1.f, 1.f, 0.f, "Channel 1 gain", "%", 0, 100);
	configParam(MOD1_PARAM, -1.f, 1.f, 0.f, "Channel 2 gain", "%", 0, 100);
	configParam(MOD2_PARAM, -1.f, 1.f, 0.f, "Channel 3 gain", "%", 0, 100);
	configParam(MOD3_PARAM, -1.f, 1.f, 0.f, "Channel 4 gain", "%", 0, 100);
	configParam(HARMONIC1_PARAM, -2.62148837674, 1.37851162325f, -0.62148837674, "Harmonic 1 Frequency", "Hz", 2, dsp::FREQ_A4);
	configParam(HARMONIC2_PARAM, -2.39334242818, 1.60665757182, -0.39334242818, "Harmonic 2 Frequency", "Hz", 2, dsp::FREQ_A4);
	configParam(HARMONICSPACING_PARAM, 0.f, 10.f, 5.f, "Harmonics Spacing", "Hz", 0.f, 20.f, 25.f);
	configParam(HARMONICDECAY_PARAM, -2.f, 0.f, -1.f, "Harmonics Decay Time", "s", 10.f, 1.f);
	configParam(HARMONICAMP_PARAM, 0.f, 1.f, 0.5f, "Harmonics Amplitude Gain", "db", -10.f, 40.f);
	configParam(FMTONE_PARAM, -5.f, 5.f, 0.f, "FM Tone Frequency", "Hz", 2, dsp::FREQ_A4);
	configParam(FMCHARACTER_PARAM, -5.f, 5.f, 0.f, "FM Character Frequency", "Hz", 2, dsp::FREQ_A4);
	configParam(FMDEPTH_PARAM, 0.f, 1.f, 0.5f, "FM Depth", "%", 0, 100);
	configParam(FMFEEDBACK_PARAM, 0.f, 1.f, 0.5f, "FM Feedback Amount", "%", 0, 100);
	configParam(FMAMP_PARAM, 0.f, 1.f, 0.5f, "FM Amplitude Gain", "db", -10.f, 40.f);
	configParam(NOISECOLOR_PARAM, 0.f, 5.f, 0.f, "Noise Color");
	configParam(RINGMODULATION_PARAM, 0.f, 1.f, 0.5f, "Ring Modulation Amplitude Gain", "db", -10.f, 40.f);
	configParam(NOISEAMP_PARAM, 0.f, 1.f, 0.5f, "Noise Amplitude Gain", "db", -10.f, 40.f);
	configParam(VELOCITY_PARAM, 0.f, 10.f, 5.f, "Velocity");
	configParam(SNAREDECAY_PARAM, -2.f, 0.f, -1.f, "Snare Decay Time", "s", 10.f, 1.f);
	configParam(SNAREAMP_PARAM, 0.f, 1.f, 0.5f, "Snare Amplitude Gain", "db", -10.f, 40.f);
	configParam(AUTONOTCH_PARAM, 0.f, 1.f, 0.f, "Auto Notch");
	configParam(MASTERAMP_PARAM, 0.f, M_SQRT2, 1.f, "Master Amplitude Gain", "db", -10.f, 40.f);
	configParam(NOTCH1_PARAM, -5.f, 5.f, -1.f, "Notch 1 Frequency", "Hz", 2, dsp::FREQ_A4);
	configParam(NOTCH2_PARAM, -5.f, 5.f, 0.f, "Notch 2 Frequency", "Hz", 2, dsp::FREQ_A4);
	configParam(NOTCH3_PARAM, -5.f, 5.f, 1.f, "Notch 3 Frequency", "Hz", 2, dsp::FREQ_A4);
	configParam(LPF_PARAM, -5.f, 5.f, 5.f, "LPF Cutoff Frequency", "Hz", 2, dsp::FREQ_A4);
	configParam(HPF_PARAM, -5.f, 5.f, -5.f, "HPF Cutoff Frequency", "Hz", 2, dsp::FREQ_A4);

	SnareControls *controls = new SnareControls(&params, &outputs, &inputs, &lights);
	engine = new SnareEngine(controls);
}
void Snare::process(const ProcessArgs& args) {
	engine->process(args.sampleRate, args.sampleTime);
}

json_t* Snare::dataToJson()
{
	json_t *rootJ = json_object();
	json_object_set_new(rootJ, "modMatrix", engine->controls->modMatrixToJson());
	return rootJ;
}

void Snare::dataFromJson(json_t *rootJ)
{
	json_t *modMatrix = json_object_get(rootJ, "modMatrix");
	if (modMatrix != NULL)
		{
			engine->controls->modMatrixFromJson(modMatrix);
		}
}

std::map<int, int> Snare::paramToRow =  
{
        {BASEFQ_PARAM, 0}, {BASEDECAY_PARAM, 1}, {BASEAMP_PARAM, 2},
        {HARMONIC1_PARAM, 3}, {HARMONIC2_PARAM, 4}, {HARMONICSPACING_PARAM, 5},
        {HARMONICDECAY_PARAM, 6}, {HARMONICAMP_PARAM, 7}, {FMTONE_PARAM, 8},
        {FMCHARACTER_PARAM, 9}, {FMDEPTH_PARAM, 10}, {FMFEEDBACK_PARAM, 11},
        {FMAMP_PARAM, 12}, {NOISECOLOR_PARAM, 13}, {RINGMODULATION_PARAM, 14},
        {NOISEAMP_PARAM, 15}, {VELOCITY_PARAM, 16}, {SNAREDECAY_PARAM, 17},
        {SNAREAMP_PARAM, 18}, {NOTCH1_PARAM, 19}, {NOTCH2_PARAM, 20},
        {NOTCH3_PARAM, 21}, {LPF_PARAM, 22}, {HPF_PARAM, 23},
        {MASTERAMP_PARAM, 24} 
};

//Model* modelSnare = createModel<Snare, SnareWidget>("Snare");