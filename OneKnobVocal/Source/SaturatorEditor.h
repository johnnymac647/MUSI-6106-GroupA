/*
  ==============================================================================

    SaturatorEditor.h
    Created: 6 Feb 2022 4:51:40pm
    Author:  yinsile

  ==============================================================================
*/

#pragma once
#include "PluginProcessor.h"
#include "ModdedNormalisableRange.h"

class SaturatorEditor : public juce::AudioProcessorEditor,
    public juce::Slider::Listener
{
public:
    SaturatorEditor(OneKnobVocalAudioProcessor&);
    ~SaturatorEditor();
    void paint(juce::Graphics&) override;
    void sliderValueChanged(juce::Slider* slider) override;
    void updateRanges();
private:
    OneKnobVocalAudioProcessor& mProcessor;
    juce::Slider GainKnob;
    juce::Slider MixKnob;
    juce::Slider VolumeKnob;

    juce::Label GainKnobLabel;
    juce::Label MixKnobLabel;
    juce::Label VolumeKnobLabel;

    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> GainKnobAttach;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> MixKnobAttach;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> VolumeKnobAttach;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SaturatorEditor);
};
