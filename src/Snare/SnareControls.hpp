#pragma once
#include "../common/PercussionControls.hpp"


namespace snare {
class SnareControls : public PercussionControls {
    public:
    SnareControls(vector<Param>* p, vector<Output>* o, vector<Input>* i, vector<Light>* l);
    ~SnareControls();
    // Mod Matrix tools
    int getModMatrixEntry(int i, int j);
    void toggleModMatrixEntry(int i, int j);
    int getModMatrixRowCount(int i);
    json_t *modMatrixToJson();
    void modMatrixFromJson(json_t *modMatrix);  

    // All PercussionControls provide these tools
    void setOutputVoltage(float val) override;
    // Gets longest of the three decay elements in [0.01, 1]s
    float getLongestDecay() override;
    // Gets trigger
    float getTrigger() override;

    private:
    int **_modMatrix;
};
} //namespace snare