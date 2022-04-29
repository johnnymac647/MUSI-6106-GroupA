/*
  ==============================================================================

    ReverbEditor.h
    Created: 6 Feb 2022 4:51:25pm
    Author:  yinsile

  ==============================================================================
*/

#pragma once
#include "PluginProcessor.h"
#include "ModdedNormalisableRange.h"
#include "Reverb.h"

class ReverbEditor : public juce::Component,
    public juce::Slider::Listener
{
public:
    ReverbEditor(OneKnobVocalAudioProcessor&);
    ~ReverbEditor();
    void paint(juce::Graphics&) override;
    void sliderValueChanged(juce::Slider* slider) override;
    void updateRanges();
    void changeToggleStateOnClick(juce::Button* button)
    {
        auto state = button->getToggleState();
        juce::String selectedString = state ? "-" : "+";

        button->setButtonText(selectedString);

        for (int i = 0; i < Reverb::effectParameters::kNumOfParameters; i++)
        {
            if (button == &flipToggleButtons[i])
            {
                mProcessor.mappingRangeFlip.set(Reverb::parameterIDs[i], state);
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
        for (int i = 0; i < Reverb::effectParameters::kNumOfParameters; i++)
        {
            updateToggleStateFromProcessor(&flipToggleButtons[i], Reverb::parameterIDs[i]);
        }
    }
private:
    OneKnobVocalAudioProcessor& mProcessor;

    juce::Slider editorSliders[Reverb::effectParameters::kNumOfParameters];
    juce::Label editorLabels[Reverb::effectParameters::kNumOfParameters];
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> sliderAttachments[Reverb::effectParameters::kNumOfParameters];
    juce::TextButton flipToggleButtons[Reverb::effectParameters::kNumOfParameters];

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ReverbEditor);
};