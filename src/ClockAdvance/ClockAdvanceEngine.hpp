#pragma once
#include "../common/ModuleEngine.hpp"
#include "ClockAdvanceControls.hpp"
#include <dsp/digital.hpp>

using namespace rack::dsp;

class BPMClock {
    public:
    BPMClock() {

    }
    bool goodBPM()
    {
        return timeBetweenEdges0 && (timeBetweenEdges0 == timeBetweenEdges1);
    }
    void update(float newTime)
    {
        timeBetweenEdges1 = timeBetweenEdges0;
        timeBetweenEdges0 = newTime;
    }
    int getBPM()
    {
        if (goodBPM())
        {
            return round(60.f / timeBetweenEdges0);
        }
        return 0.f;
    }
    float getSecPerBeat() {
        if (goodBPM())
        {
            return timeBetweenEdges0;
        }
    }
    private:
    float timeBetweenEdges0 = 0;
    float timeBetweenEdges1 = 0;
};

namespace clockAdvance {
    class ClockAdvanceEngine : ModuleEngine {
        ClockAdvanceControls *controls;
        public:
        ClockAdvanceEngine(ClockAdvanceControls *controls)
        {
            this->controls = controls;
        }
        ~ClockAdvanceEngine()
        {
            delete controls;
        }
        void process(float sampleRate, float sampleTime) override;
        std::string strInvalidState = std::string("---");
        std::string strBPM = strInvalidState;
        std::string strNotesNum = strInvalidState;
        std::string strNotesDenom = strInvalidState;
        std::string strMS = strInvalidState;
        private:
        void updateState(float sampleRate, float sampleTime);
        void updateNotes();
        void updateMS();
        BPMClock _clock;
        float _secSinceRisingEdge = 0;
        rack::dsp::SchmittTrigger _trigger;
        float _delaySec = 0;
        int _notesNum;
        int _notesDenom;
        float _advanceSec;
    };
}