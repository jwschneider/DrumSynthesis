#include "SnareEngine.hpp"
#include "SnareControls.hpp"
#include "Snare.hpp"

using namespace snare;

SnareEngine::SnareEngine(SnareControls *controls) : PercussionEngine(controls)
{
    this->controls = controls;
}
SnareEngine::~SnareEngine()
{
    delete controls;
}
