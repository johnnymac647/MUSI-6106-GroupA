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
#include "Saturator.h"

class SaturatorEditor : public juce::AudioProcessorEditor,
    public juce::Slider::Listener
{
public:
    SaturatorEditor(OneKnobVocalAudioProcessor&);
    ~SaturatorEditor();
    void paint(juce::Graphics&) override;
    void sliderValueChanged(juce::Slider* slider) override;
    void updateRanges();
    void changeToggleStateOnClick(juce::Button* button)
    {
        auto state = button->getToggleState();
        juce::String selectedString = state ? "-" : "+";

        button->setButtonText(selectedString);

        for (int i = 0; i < Saturator::effectParameters::kNumOfParameters; i++)
        {
            if (button == &flipToggleButtons[i])
            {
                mProcessor.mappingRangeFlip.set(Saturator::parameterIDs[i], state);
                break;
            }

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
        for (int i = 0; i < Saturator::effectParameters::kNumOfParameters; i++)
        {
            updateToggleStateFromProcessor(&flipToggleButtons[i], Saturator::parameterIDs[i]);
        }
    }
private:
    OneKnobVocalAudioProcessor& mProcessor;

    juce::Slider editorSliders[Saturator::effectParameters::kNumOfParameters];
    juce::Label editorLabels[Saturator::effectParameters::kNumOfParameters];
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> sliderAttachments[Saturator::effectParameters::kNumOfParameters];
    juce::TextButton flipToggleButtons[Saturator::effectParameters::kNumOfParameters];

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SaturatorEditor);
};
