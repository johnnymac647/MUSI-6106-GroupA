/*
  ==============================================================================

    DeEsserEditor.h
    Created: 6 Feb 2022 4:50:53pm
    Author:  yinsile

  ==============================================================================
*/

#pragma once
#include "PluginProcessor.h"
#include "ModdedNormalisableRange.h"

class DeEsserEditor : public juce::AudioProcessorEditor,
    public juce::Slider::Listener
{
public:
    DeEsserEditor(OneKnobVocalAudioProcessor&);
    ~DeEsserEditor() override;
    void paint(juce::Graphics&) override;
    void sliderValueChanged(juce::Slider* slider) override;

    void updateRanges();
private:
    OneKnobVocalAudioProcessor& mProcessor;
    juce::Slider VolumeKnob;
    juce::Slider ThresholdKnob;
    juce::Slider AttackKnob;
    juce::Slider ReleaseKnob;
    juce::Slider RatioKnob;
    juce::Slider CrossoverFreqKnob;

    juce::Label VolumeKnobLabel;
    juce::Label ThresholdKnobLabel;
    juce::Label AttackKnobLabel;
    juce::Label ReleaseKnobLabel;
    juce::Label RatioKnobLabel;
    juce::Label CrossoverFreqKnobLabel;

    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> VolumeKnobAttach;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> ThresholdKnobAttach;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> RatioKnobAttach;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> AttackKnobAttach;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> ReleaseKnobAttach;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> CrossoverFreqKnobAttach;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DeEsserEditor);

};
