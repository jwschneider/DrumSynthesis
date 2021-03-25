#include "ClockAdvance.hpp"

using namespace clockAdvance;



ClockAdvance::ClockAdvance() {
	config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
	configParam(BEATSNUMERATOR_PARAM, 0.f, 1.f, 0.f, "");
	configParam(BEATSDENOMINATOR_PARAM, 0.f, 1.f, 0.f, "");
	configParam(SWITCH_PARAM, 0.f, 1.f, 0.f, "");
	configParam(MS_PARAM, 0.f, 1.f, 0.f, "");
	
	ClockAdvanceControls *controls = new ClockAdvanceControls(&params, &outputs, &inputs, &lights);
	engine = new ClockAdvanceEngine(controls);
}

void ClockAdvance::process(const ProcessArgs& args) {
	engine->process(args.sampleRate, args.sampleTime);
}

//Model* modelClockAdvance = createModel<ClockAdvance, ClockAdvanceWidget>("ClockAdvance");