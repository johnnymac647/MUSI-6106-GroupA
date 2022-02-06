/*
  ==============================================================================

    EqualizerEditor.h
    Created: 6 Feb 2022 4:51:05pm
    Author:  yinsile

  ==============================================================================
*/

#pragma once
#include "Equalizer.h"
class EqualizerEditor : public juce::AudioProcessorEditor
{
public:
    EqualizerEditor(Equalizer&);
    ~EqualizerEditor() override;
    void paint(juce::Graphics&) override;
private:
    Equalizer& mProcessor;
    juce::Slider VolumeKnob;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> VolumeKnobAttach;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(EqualizerEditor);
};
