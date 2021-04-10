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

float SnareControls::getParam(int param)
{
    float pval = ModuleControls::getParam(param);
    int row = Snare::paramToRow[param];
    if (getModMatrixRowCount(row))
    {
        for (int col = 0; col < Snare::MOD_MATRIX_COLUMNS; col++)
        {
            float mval = getInput(Snare::MOD0_INPUT + col) * getParam(Snare::MOD0_PARAM + col) * getModMatrixEntry(row, col);
            pval += mval;
        }
    }
    return pval;
}

void SnareControls::setOutputVoltage(float val)
{
    setOutput(Snare::OUTPUT_OUTPUT, val * 5.f);;
}
float SnareControls::getLongestDecay()
{
    return getBaseDecay();
}
float SnareControls::getTrigger()
{
    return getInput(Snare::TRIGGER_INPUT);
}

float SnareControls::getBaseFQ()
{
    float pval = getParam(Snare::BASEFQ_PARAM);
    pval = clamp(pval, -5.f, 5.f);
    return dsp::FREQ_C4 * std::pow(2, pval);
}
float SnareControls::getBaseDecay()
{
    float pval = getParam(Snare::BASEDECAY_PARAM);
    pval = clamp(pval, -5.f, 5.f);
    return std::pow(10, pval);
}
float SnareControls::getBaseAmp()
{
    float pval = getParam(Snare::BASEAMP_PARAM);
    pval = clamp(pval, 0.f, 1.f);
    return pval;
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

void SnareControls::setModMatrixEntry(int i, int j, int val)
{
    _modMatrix[i][j] = val;
}

int SnareControls::getModMatrixRowCount(int i)
{
    return _modMatrix[i][Snare::MOD_MATRIX_COLUMNS];
}
json_t *SnareControls::modMatrixToJson()
{
    //DEBUG("modMatrix: %d", _modMatrix);
    json_t *modMatrix = json_array();
    for (int i = 0; i < Snare::MOD_MATRIX_ROWS; i++)
    {
        json_t *row = json_array();
        for (int j = 0; j < Snare::MOD_MATRIX_COLUMNS + 1; j++)
        {
            //DEBUG("modMatrix i, j = %d, %d", i, j);
            json_array_append_new(row, json_integer(getModMatrixEntry(i, j)));
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
                setModMatrixEntry(i, j, json_integer_value(entry));
            }
        }
    }
}