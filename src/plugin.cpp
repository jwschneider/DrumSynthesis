#include "plugin.hpp"
#include "MyModule/MyModule.hpp"


Plugin* pluginInstance;


void init(Plugin* p) {
	pluginInstance = p;

	// Add modules here
	// p->addModel(modelMyModule);
	p->addModel(createModel<mymodule::MyModule, mymodule::MyModulePanel>("MyModule"));

	// Any other plugin initialization may go here.
	// As an alternative, consider lazy-loading assets and lookup tables when your module is created to reduce startup times of Rack.
}
