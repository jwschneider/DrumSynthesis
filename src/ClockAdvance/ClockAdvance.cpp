#include "ClockAdvance.hpp"

using namespace clockAdvance;



ClockAdvance::ClockAdvance() {
	config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
	configParam(NOTESNUMERATOR_PARAM, 0.f, 512.f, 1.f, "Notes Numerator");
	configParam(NOTESDENOMINATOR_PARAM, 0.f, 9.f, 3.f, "Notes Denominator", "", 2.f, 1.f);
	configParam(SWITCH_PARAM, 0.f, 1.f, 0.f, "Mode");
	configParam(MS_PARAM, 0.f, 999.f, 50.f, "MS");
	
	ClockAdvanceControls *controls = new ClockAdvanceControls(&params, &outputs, &inputs, &lights);
	engine = new ClockAdvanceEngine(controls);
}

void ClockAdvance::process(const ProcessArgs& args) {
	engine->process(args.sampleRate, args.sampleTime);
}

//Model* modelClockAdvance = createModel<ClockAdvance, ClockAdvanceWidget>("ClockAdvance");