#include "SnareControls.hpp"
#include "Snare.hpp"

using namespace snare;

SnareControls::SnareControls(vector<Param>* p, vector<Output>* o, vector<Input>* i, vector<Light>* l) : PercussionControls {p, o, i, l}
{
    _modMatrix = new int*[Snare::MOD_MATRIX_ROWS];
    for (uint32_t i = 0; i < Snare::MOD_MATRIX_ROWS; i++)
    {
        _modMatrix[i] = new int[Snare::MOD_MATRIX_COLUMNS + 1] {0};
    }
}
SnareControls::~SnareControls()
{
    delete[] _modMatrix;
}

void SnareControls::setOutputVoltage(float val)
{
    0;
}
float SnareControls::getLongestDecay()
{
    0;
}
float SnareControls::getTrigger()
{
    0;
}

int SnareControls::getModMatrixEntry(int i, int j)
{
    return _modMatrix[i][j];
}
void SnareControls::toggleModMatrixEntry(int i, int j)
{
    int val = _modMatrix[i][j];
    if (val)
    {
        _modMatrix[i][Snare::MOD_MATRIX_COLUMNS]--;
        _modMatrix[i][j] = 0;
    }
    else
    {
        _modMatrix[i][Snare::MOD_MATRIX_COLUMNS]++;
        _modMatrix[i][j] = 1;
    }
}
int SnareControls::getModMatrixRowCount(int i)
{
    return _modMatrix[i][Snare::MOD_MATRIX_COLUMNS];
}
json_t *SnareControls::modMatrixToJson()
{
    json_t *modMatrix = json_array();
    for (int i = 0; i < Snare::MOD_MATRIX_ROWS; i++)
    {
        json_t *row = json_array();
        for (int j = 0; j < Snare::MOD_MATRIX_COLUMNS + 1; j++)
        {
            json_array_append_new(row, json_integer(_modMatrix[i][j]));
        }
        json_array_append(modMatrix, row);
    }
    return modMatrix;
}
void SnareControls::modMatrixFromJson(json_t *modMatrix)
{
    for (int i = 0; i < Snare::MOD_MATRIX_ROWS; i++)
    {
        json_t *row = json_array_get(modMatrix, i);
        {
            for (int j = 0; j < Snare::MOD_MATRIX_COLUMNS + 1; j++)
            {
                json_t *entry = json_array_get(row, j);
                _modMatrix[i][j] = json_integer_value(entry);
            }
        }
    }
}