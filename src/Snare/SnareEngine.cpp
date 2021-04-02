#include "SnareEngine.hpp"
#include "SnareControls.hpp"
#include "Snare.hpp"

using namespace snare;

SnareEngine::SnareEngine(SnareControls *controls)
{
    this->controls = controls;
    _modMatrix = new int*[Snare::NUM_PARAMS];
    for (uint32_t i = 0; i < Snare::NUM_PARAMS; i++)
    {
        _modMatrix[i] = new int[Snare::NUM_MODULATORS + 1] {0};
    }
}
SnareEngine::~SnareEngine()
{
    delete controls;
    // for (int i = 0; i < sizeof(_modMatrix); i++)
    // {
    //     delete _modMatrix[i];
    // }   
    delete[] _modMatrix;
}
int SnareEngine::getModMatrixEntry(int i, int j)
{
    return _modMatrix[i][j];
}
void SnareEngine::toggleModMatrixEntry(int i, int j)
{
    int val = _modMatrix[i][j];
    if (val)
    {
        _modMatrix[i][Snare::NUM_MODULATORS]--;
        _modMatrix[i][j] = 0;
    }
    else
    {
        _modMatrix[i][Snare::NUM_MODULATORS]++;
        _modMatrix[i][j] = 1;
    }
}
int SnareEngine::getModMatrixRowCount(int i)
{
    return _modMatrix[i][Snare::NUM_MODULATORS];
}
void SnareEngine::process(float sampleRate, float sampleTime)
{

}