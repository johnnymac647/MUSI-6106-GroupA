/*
  ==============================================================================

    GateEditor.h
    Created: 6 Feb 2022 4:51:17pm
    Author:  yinsile

  ==============================================================================
*/

#pragma once
#include "PluginProcessor.h"

class GateEditor : public juce::AudioProcessorEditor
{
public:
    GateEditor(OneKnobVocalAudioProcessor&);
    ~GateEditor() override;
    void paint(juce::Graphics&) override;
private:
    OneKnobVocalAudioProcessor& mProcessor;
    juce::Slider VolumeKnob;
    juce::Slider ThresholdKnob;
    juce::Slider AttackKnob;
    juce::Slider ReleaseKnob;
    juce::Slider RatioKnob;

    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> VolumeKnobAttach;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> ThresholdKnobAttach;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> RatioKnobAttach;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> AttackKnobAttach;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> ReleaseKnobAttach;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(GateEditor);
};
