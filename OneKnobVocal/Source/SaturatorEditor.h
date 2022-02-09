/*
  ==============================================================================

    SaturatorEditor.h
    Created: 6 Feb 2022 4:51:40pm
    Author:  yinsile

  ==============================================================================
*/

#pragma once
#include "Saturator.h"

class SaturatorEditor : public juce::AudioProcessorEditor
{
public:
    SaturatorEditor(Saturator&);
    ~SaturatorEditor();
    void paint(juce::Graphics&) override;
private:
    Saturator& mProcessor;
    juce::Slider VolumeKnob;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> VolumeKnobAttach;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SaturatorEditor);
};