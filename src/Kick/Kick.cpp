#include "Kick.hpp"

using namespace kick;

const float sqrt2 = 1.41421356237309504880;

Kick::Kick() {
	config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
	configParam(LOW_FUNDAMENTAL_PARAM, 10.f, 50.f, 30.f, "Low Fundamental FQ", "Hz");
	configParam(LOW_PARTIALS_PARAM, 0, 16, 8, "Number of partials");
	configParam(LOW_SPREAD_PARAM, 0.f, 90.f, 45.f, "Voice Spread", "Hz");
	configParam(LOW_BEND_PARAM, -1.f, 1.f, 0.f, "Bend in decay of partial magnitude");
	configParam(LOW_DECAY_PARAM, -2.f, 0.f, -1.f, "Decay time", "s", 10.f, 1.f);
	configParam(LOW_LEVEL_PARAM, 0.f, sqrt2, 1.f, "Fundamental level", "db", -10.f, 40.f);
	configParam(MID_TONE_PARAM, 0.f, 1.f, 0.f, "");
	configParam(MID_CHARACTER_PARAM, 0.f, 1.f, 0.f, "");
	configParam(MID_LP_PARAM, 0.f, 1.f, 0.f, "");
	configParam(MID_HP_PARAM, 0.f, 1.f, 0.f, "");
	configParam(MID_DECAY_PARAM, 0.f, 1.f, 0.f, "");
	configParam(MID_LEVEL_PARAM, 0.f, 1.f, 0.f, "");
	configParam(HEAD_TONE_PARAM, 0.f, 1.f, 0.f, "");
	configParam(HEAD_CHARACTER_PARAM, 0.f, 1.f, 0.f, "");
	configParam(HEAD_LP_PARAM, 0.f, 1.f, 0.f, "");
	configParam(HEAD_HP_PARAM, 0.f, 1.f, 0.f, "");
	configParam(HEAD_DECAY_PARAM, 0.f, 1.f, 0.f, "");
	configParam(HEAD_LEVEL_PARAM, 0.f, 1.f, 0.f, "");

	KickControls *controls = new KickControls(&params, &outputs, &inputs, &lights);
	engine = new KickEngine(controls);
}

void Kick::process(const ProcessArgs& args)
{
	engine->process(args.sampleRate, args.sampleTime);
}