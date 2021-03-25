#include "plugin.hpp"
#include "MyModule/MyModule.hpp"
#include "Kick/Kick.hpp"
#include "ClockAdvance/ClockAdvance.hpp"


Plugin* pluginInstance;


void init(Plugin* p) {
	pluginInstance = p;

	// Add modules here
	// p->addModel(modelMyModule);
	p->addModel(createModel<mymodule::MyModule, mymodule::MyModulePanel>("MyModule"));
	p->addModel(createModel<kick::Kick, kick::KickPanel>("Kick"));
	p->addModel(createModel<clockAdvance::ClockAdvance, clockAdvance::ClockAdvancePanel>("ClockAdvance"));
	// Any other plugin initialization may go here.
	// As an alternative, consider lazy-loading assets and lookup tables when your module is created to reduce startup times of Rack.
}
