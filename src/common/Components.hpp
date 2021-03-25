#include <rack.hpp>
#include "../plugin.hpp"

extern Plugin* pluginInstance;

using namespace rack::app;

struct SnapKnobSmallNonDirectional : SVGKnob {
    SnapKnobSmallNonDirectional() {
        minAngle = std::numeric_limits<float>::min();
        maxAngle = std::numeric_limits<float>::max();
        //snap = true;
        setSvg(APP->window->loadSvg(asset::plugin(pluginInstance, "res/KnobSmallNonDirectional.svg")));
    }
};

struct DSSwitch : SvgSwitch {
    DSSwitch() {
        addFrame(APP->window->loadSvg(asset::plugin(pluginInstance, "res/Switch_0.svg")));
        addFrame(APP->window->loadSvg(asset::plugin(pluginInstance,"res/Switch_1.svg")));
    }
};

struct DSIPort : SvgPort {
    DSIPort() {
        setSvg(APP->window->loadSvg(asset::plugin(pluginInstance,"res/PortInput.svg")));
    }
};

struct DSOPort : SvgPort {
    DSOPort() {
        setSvg(APP->window->loadSvg(asset::plugin(pluginInstance,"res/PortOutput.svg")));
    }
};

