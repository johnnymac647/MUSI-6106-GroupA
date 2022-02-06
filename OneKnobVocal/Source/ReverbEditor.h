/*
  ==============================================================================

    ReverbEditor.h
    Created: 6 Feb 2022 4:51:25pm
    Author:  yinsile

  ==============================================================================
*/

#pragma once
#include "Reverb.h"

class ReverbEditor : public juce::AudioProcessorEditor
{
public:
    ReverbEditor(Reverb&);
    ~ReverbEditor();
    void paint(juce::Graphics&) override;
private:
    Reverb& mProcessor;
    juce::Slider VolumeKnob;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> VolumeKnobAttach;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ReverbEditor);
};