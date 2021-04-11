#pragma once
#include "../common/PercussionControls.hpp"
#include "jansson.h"


namespace snare {
class SnareControls : public PercussionControls {
    public:
    SnareControls(vector<Param>* p, vector<Output>* o, vector<Input>* i, vector<Light>* l);
    ~SnareControls();

    // A redefined version of ModuleControls::getParam that takes the Mod Matrix into account
    float getParam(int param);

    // All PercussionControls provide these tools
    // val should be in [-1, 1]
    void setOutputVoltage(float val) override;
    // Gets longest of the three decay elements in [0.01, 1]s
    float getLongestDecay() override;
    // Gets trigger
    float getTrigger() override;
    // Gets the frequecy of the base oscillator
    float getBaseFQ();
    // Gets the decay time of the base oscillator in seconds
    float getBaseDecay();
    // Get the base amplitude gain
    float getBaseAmp();

    // Mod Matrix tools
    int getModMatrixEntry(int i, int j);
    void toggleModMatrixEntry(int i, int j);
    void setModMatrixEntry(int i, int j, int val);
    int getModMatrixRowCount(int i);
    json_t *modMatrixToJson();
    void modMatrixFromJson(json_t *modMatrix);

    const static int MOD_MATRIX_COLUMNS = 5;
    const static int MOD_MATRIX_ROWS = 25;
    const static int MOD_MATRIX_PANEL_COLUMNS = MOD_MATRIX_COLUMNS - 1;
    const static int MOD_MATRIX_PANEL_ROWS = MOD_MATRIX_ROWS;

    private:
    void incrementModMatrixRowCount(int i);
    void decrementModMatrixRowCount(int i);
    int _modMatrix[MOD_MATRIX_COLUMNS * MOD_MATRIX_ROWS] = {0};
};
} //namespace snare