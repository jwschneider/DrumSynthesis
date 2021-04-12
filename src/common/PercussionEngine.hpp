#pragma once
#include "ModuleEngine.hpp"
#include "PercussionControls.hpp"
#include <dsp/digital.hpp>

using namespace rack::dsp;

class PercussionSection
{
    public:
    PercussionSection() {}
    virtual ~PercussionSection() = default;
    virtual void init(float sampleRate) = 0;
    virtual float process(float sampleRate, float sampleTime) = 0;
    virtual void reset() = 0;
};

class PercussionEngine : public ModuleEngine
{
        public:
        PercussionEngine(PercussionControls *controls)
        {
            this->controls = controls;
            _ON = false;
        }
        ~PercussionEngine()
        {
            reset();
            while (!sections.empty())
            {
                delete sections.back();
                sections.pop_back();
            }
            delete controls;
        }
        void process(float sampleRate, float sampleTime) override
        {
            updateState(sampleRate, sampleTime);
            if (_ON) {
                float out = 0;
                std::for_each(sections.begin(), sections.end(), [=, &out] (PercussionSection *sec) 
                    { out += sec->process(sampleRate, sampleTime); }
                );
                controls->setOutputVoltage(out);
            }
        }
        protected:
        void init(float sampleRate) 
        {
            std::for_each(sections.begin(), sections.end(), [=] (PercussionSection *sec) {sec->init(sampleRate);});
        }
        void reset()
        {
            std::for_each(sections.begin(), sections.end(), [] (PercussionSection *sec) {sec->reset();});
        }
        void updateState(float sampleRate, float sampleTime)
        {
            bool trig = trigger.process(controls->getTrigger());
            if (trig)
            {
                reset();
                init(sampleRate);
                _ON = true;
                _currentTime = 0.f;
                _endTime = controls->getLongestDecay();
            }
            else if (_ON)
            {
                _currentTime += sampleTime;
                _ON = _currentTime < _endTime;
            }
            else
            {
                //reset();
            }
        }
        PercussionControls *controls;
        std::vector<PercussionSection *> sections;
        bool _ON;
        float _currentTime;
        float _endTime;
        rack::dsp::SchmittTrigger trigger;    
};