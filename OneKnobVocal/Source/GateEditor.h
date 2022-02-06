/*
  ==============================================================================

    GateEditor.h
    Created: 6 Feb 2022 4:51:17pm
    Author:  yinsile

  ==============================================================================
*/

#pragma once
#include "Gate.h"

class GateEditor : public juce::AudioProcessorEditor
{
public:
    GateEditor(Gate&);
    ~GateEditor() override;
    void paint(juce::Graphics&) override;
private:
    Gate& mProcessor;
    juce::Slider VolumeKnob;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> VolumeKnobAttach;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(GateEditor);
};
