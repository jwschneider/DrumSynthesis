#include "SnareControls.hpp"
#include "Snare.hpp"

using namespace snare;

SnareControls::SnareControls(vector<Param>* p, vector<Output>* o, vector<Input>* i, vector<Light>* l) : PercussionControls {p, o, i, l}
{
    // _modMatrix = new int*[Snare::MOD_MATRIX_ROWS];
    // for (int i = 0; i < Snare::MOD_MATRIX_ROWS; i++)
    // {
    //     _modMatrix[i] = new int[Snare::MOD_MATRIX_COLUMNS + 1] {0};
    // }
    
}
SnareControls::~SnareControls()
{
    
}


float SnareControls::getParam(int param)
{
    float pval = ModuleControls::getParam(param);
    int row = Snare::paramToRow[param];
    if (getModMatrixRowCount(row))
    {
        for (int col = 0; col < SnareControls::MOD_MATRIX_PANEL_COLUMNS; col++)
        {
            DEBUG("row, col: %d, %d", row, col);
            float mval = ModuleControls::getInput(Snare::MOD0_INPUT + col) * ModuleControls::getParam(Snare::MOD0_PARAM + col) * getModMatrixEntry(row, col);
            DEBUG("mval: %f", mval);
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
    return _modMatrix[i*MOD_MATRIX_COLUMNS + j];
}

void SnareControls::setModMatrixEntry(int i, int j, int val)
{
    _modMatrix[i*MOD_MATRIX_COLUMNS + j] = val;
}

void SnareControls::toggleModMatrixEntry(int i, int j)
{
    int val = getModMatrixEntry(i, j);
    if (val)
    {
        decrementModMatrixRowCount(i);
        setModMatrixEntry(i, j, 0);
    }
    else
    {
        incrementModMatrixRowCount(i);
        setModMatrixEntry(i, j, 1);
    }
}

int SnareControls::getModMatrixRowCount(int i)
{
    return getModMatrixEntry(i, MOD_MATRIX_COLUMNS - 1);
}

void SnareControls::incrementModMatrixRowCount(int i)
{
    _modMatrix[(i+1)*(MOD_MATRIX_COLUMNS) - 1]++;
}
void SnareControls::decrementModMatrixRowCount(int i)
{
    _modMatrix[(i+1)*(MOD_MATRIX_COLUMNS) - 1]--;
}

json_t *SnareControls::modMatrixToJson()
{
    //DEBUG("modMatrix: %d", _modMatrix);
    json_t *modMatrix = json_array();
    for (int i = 0; i < MOD_MATRIX_ROWS; i++)
    {
        json_t *row = json_array();
        for (int j = 0; j < MOD_MATRIX_COLUMNS; j++)
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
    if (json_is_array(modMatrix))
    {
        for (int i = 0; i < MOD_MATRIX_ROWS; i++)
        {
            json_t *row = json_array_get(modMatrix, i);
            if (json_is_array(modMatrix))
            {
                for (int j = 0; j < MOD_MATRIX_COLUMNS; j++)
                {
                    json_t *entry = json_array_get(row, j);
                    setModMatrixEntry(i, j, json_integer_value(entry));
                }
            }
        }
    }
}