/*
  ==============================================================================

    GateEditor.h
    Created: 6 Feb 2022 4:51:17pm
    Author:  yinsile

  ==============================================================================
*/

#pragma once
#include "PluginProcessor.h"
#include "ModdedNormalisableRange.h"

class GateEditor : public juce::AudioProcessorEditor,
    public juce::Slider::Listener
{
public:
    GateEditor(OneKnobVocalAudioProcessor&);
    ~GateEditor() override;
    void paint(juce::Graphics&) override;
    void sliderValueChanged(juce::Slider* slider) override;
    void updateRanges();
    void updateToggleState(juce::Button* button)
    {
        auto state = button->getToggleState();
        juce::String stateString = state ? "ON" : "OFF";
        juce::String selectedString = state ? "+" : "-";

        button->setButtonText(selectedString);
    }

private:
    OneKnobVocalAudioProcessor& mProcessor;
    juce::Slider VolumeKnob;
    juce::Slider ThresholdKnob;
    juce::Slider AttackKnob;
    juce::Slider ReleaseKnob;
    juce::Slider RatioKnob;

    juce::Label VolumeKnobLabel;
    juce::Label ThresholdKnobLabel;
    juce::Label AttackKnobLabel;
    juce::Label ReleaseKnobLabel;
    juce::Label RatioKnobLabel;

    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> VolumeKnobAttach;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> ThresholdKnobAttach;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> RatioKnobAttach;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> AttackKnobAttach;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> ReleaseKnobAttach;

    juce::TextButton VolumeButton {"+"};
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(GateEditor);
};
