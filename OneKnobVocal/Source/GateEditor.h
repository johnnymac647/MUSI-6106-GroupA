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
    void changeToggleStateOnClick(juce::Button* button)
    {
        auto state = button->getToggleState();
        juce::String selectedString = state ? "-" : "+";

        button->setButtonText(selectedString);

        if (button == &VolumeButton)
        {
            mProcessor.mappingRangeFlip.set("GATE_POST_GAIN", state);
        }
        else if (button == &ThresholdButton)
        {
            mProcessor.mappingRangeFlip.set("GATE_THRESHOLD", state);
        }
        else if (button == &AttackButton)
        {
            mProcessor.mappingRangeFlip.set("GATE_ATTACK", state);
        }
        else if (button == &ReleaseButton)
        {
            mProcessor.mappingRangeFlip.set("GATE_RELEASE", state);
        }
        else if (button == &RatioButton)
        {
            mProcessor.mappingRangeFlip.set("GATE_RATIO", state);
        }
    }

    void updateToggleStateFromProcessor(juce::Button* button, juce::String id)
    {
        auto state = mProcessor.mappingRangeFlip[id];
        button->setToggleState(state, juce::dontSendNotification);
        juce::String selectedString = state ? "-" : "+";
        button->setButtonText(selectedString);
    }

    void setAllButtonState()
    {
        updateToggleStateFromProcessor(&VolumeButton, "GATE_POST_GAIN");
        updateToggleStateFromProcessor(&ThresholdButton, "GATE_THRESHOLD");
        updateToggleStateFromProcessor(&AttackButton, "GATE_ATTACK");
        updateToggleStateFromProcessor(&ReleaseButton, "GATE_RELEASE");
        updateToggleStateFromProcessor(&RatioButton, "GATE_RATIO");
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

    juce::TextButton VolumeButton{ "-" };
    juce::TextButton ThresholdButton{ "-" };
    juce::TextButton AttackButton{ "-" };
    juce::TextButton ReleaseButton{ "-" };
    juce::TextButton RatioButton{ "-" };
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(GateEditor);
};
