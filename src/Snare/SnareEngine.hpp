#pragma once
#include "../common/PercussionEngine.hpp"
#include "SnareControls.hpp"

namespace snare {
    class SnareEngine : public PercussionEngine {
        public:
        SnareEngine(SnareControls *controls);
        SnareControls *controls;
    };
}