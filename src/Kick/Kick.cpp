#include "Kick.hpp"

using namespace kick;


Kick::Kick() {
	config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
	configParam(LOW_FUNDAMENTAL_PARAM, 50.f, 120.f, 80.f, "Low Fundamental FQ", "Hz");
	configParam(LOW_PARTIALS_PARAM, 0, 16, 3, "Number of partials");
	configParam(LOW_SPREAD_PARAM, 0.f, 60.f, 25.f, "Voice Spread", "Hz");
	configParam(LOW_BEND_PARAM, 0.01f, 1.f, 0.5f, "Bend in decay of partial magnitude");
	configParam(LOW_DECAY_PARAM, -2.f, 0.f, -1.f, "Decay time", "s", 10.f, 1.f);
	configParam(LOW_LEVEL_PARAM, 0.f, M_SQRT2, 1.f, "Fundamental level", "db", -10.f, 40.f);
	configParam(MID_TONE_PARAM, -2.f, 2.f, -1.f, "Midrange Tone FQ", "Hz", 2, dsp::FREQ_A4);
	configParam(MID_CHARACTER_PARAM, -2.f, 2.f, 0.96431461047, "Midrange Character Param FQ", "Hz", 2, dsp::FREQ_A4);
	configParam(MID_LP_PARAM, -2.f, 1.f, 0.53849564831, "Low Pass FQ", "Hz", 2, dsp::FREQ_C4);
	configParam(MID_HP_PARAM, -2.f, 1.f, -1.38750377024, "High Pass FQ", "Hz", 2, dsp::FREQ_C4);
	configParam(MID_DECAY_PARAM, -2.f, 0.f, -1.f, "Midrange Decay Time", "s", 10, 1.f);
	configParam(MID_LEVEL_PARAM, 0.f, M_SQRT2, 1.f, "Midrange level", "db", -10.f, 40);
	configParam(HEAD_TONE_PARAM, 0.f, 3.4641016, 1.06593258005f, "Drum Head Tone", "Hz", 2, dsp::FREQ_A4);
	configParam(HEAD_CHARACTER_PARAM, 0.f, 3.4641016, 2.54557530244f, "Drum Head Character", "Hz", 2, dsp::FREQ_A4);
	configParam(HEAD_LP_PARAM, -1.f, 4.f, 2.27470172942f, "Head Low Pass FQ", "Hz", 2, dsp::FREQ_C4);
	configParam(HEAD_HP_PARAM, -1.f, 4.f, 1.24941081012f, "Head High Pass FQ", "Hz", 2, dsp::FREQ_C4);
	configParam(HEAD_DECAY_PARAM, -2.f, 0.f, -1.58502665203f, "Head Decay Time", "s", 10.f, 1.f);
	configParam(HEAD_LEVEL_PARAM, 0.f, M_SQRT2, 1.f, "Head Level", "db", -10.f, 40.f);

	KickControls *controls = new KickControls(&params, &outputs, &inputs, &lights);
	engine = new KickEngine(controls);
}

void Kick::process(const ProcessArgs& args)
{
	engine->process(args.sampleRate, args.sampleTime);
}