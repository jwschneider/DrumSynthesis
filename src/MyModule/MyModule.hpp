#pragma once

#include <engine/Module.hpp>
#include <app/ModuleWidget.hpp>
#include "MyModuleEngine.hpp"
#include "../plugin.hpp"

namespace mymodule {

class MyModule : public rack::engine::Module {
    public:
        MyModule();
        enum ParamIds {
            PITCH_PARAM,
            NUM_PARAMS
        };
        enum InputIds {
            PITCH_INPUT,
            NUM_INPUTS
        };
        enum OutputIds {
            SINE_OUTPUT,
            NUM_OUTPUTS
        };
        enum LightIds {
            BLINK_LIGHT,
            NUM_LIGHTS
        };

        void process(const ProcessArgs& args) override;
        
    private:
        MyModuleEngine *engine;
};


class MyModulePanel : public rack::app::ModuleWidget {
    public:
        MyModulePanel(MyModule *module);
};
} //namespace MyModule