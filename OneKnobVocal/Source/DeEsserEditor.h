/*
  ==============================================================================

    DeEsserEditor.h
    Created: 6 Feb 2022 4:50:53pm
    Author:  yinsile

  ==============================================================================
*/

#pragma once
#include "DeEsser.h"

class DeEsserEditor : public juce::AudioProcessorEditor
{
public:
    DeEsserEditor(Deesser&);
    ~DeEsserEditor() override;
    void paint(juce::Graphics&) override;
private:
    Deesser& mProcessor;
    juce::Slider VolumeKnob;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> VolumeKnobAttach;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DeEsserEditor);
};