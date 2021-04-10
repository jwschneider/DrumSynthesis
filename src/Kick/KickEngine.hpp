#pragma once
#include "../common/PercussionEngine.hpp"
#include "KickControls.hpp"
#include "../common/FMOscillator.hpp"
#include "../common/LinearDecayEnvelope.hpp"
#include <dsp/digital.hpp>
#include <dsp/filter.hpp>
#include "../common/Filter.hpp"
#include "../common/EnvelopeGenerator.hpp"

using namespace rack::dsp;

namespace kick{
    class KickEngine : public PercussionEngine {
        KickControls *controls;
        public:
        KickEngine(KickControls *controls);
    };
} //namespace Kick