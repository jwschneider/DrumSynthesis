#include <rack.hpp>
#include "../plugin.hpp"

extern Plugin* pluginInstance;

using namespace rack::app;

struct SnapKnobSmallNonDirectional : SVGKnob {
    SnapKnobSmallNonDirectional() {
        minAngle = -2 * M_PI;
        maxAngle = 2 * M_PI;
        snap = true;
        setSvg(APP->window->loadSvg(asset::plugin(pluginInstance, "res/KnobSmallNonDirectional.svg")));
    }
};
struct SnapKnobSmallDirectional : SVGKnob {
    SnapKnobSmallDirectional() {
        minAngle = -2 * M_PI;
        maxAngle = 2 * M_PI;
        snap = true;
        setSvg(APP->window->loadSvg(asset::plugin(pluginInstance, "res/KnobSmallDirectional.svg")));
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

