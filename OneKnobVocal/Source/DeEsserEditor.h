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
#include "DeEsser.h"

class DeEsserEditor : public juce::Component,
    public juce::Slider::Listener
{
public:
    DeEsserEditor(OneKnobVocalAudioProcessor&);
    ~DeEsserEditor() override;
    void paint(juce::Graphics&) override;
    void sliderValueChanged(juce::Slider* slider) override;

    void updateRanges();

    void changeToggleStateOnClick(juce::Button* button)
    {
        auto state = button->getToggleState();
        juce::String selectedString = state ? "-" : "+";

        button->setButtonText(selectedString);

        for (int i = 0; i < Deesser::effectParameters::kNumOfParameters; i++)
        {
            if (button == &flipToggleButtons[i])
            {
                mProcessor.mappingRangeFlip.set(Deesser::parameterIDs[i], state);
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
        for (int i = 0; i < Deesser::effectParameters::kNumOfParameters; i++)
        {
            updateToggleStateFromProcessor(&flipToggleButtons[i], Deesser::parameterIDs[i]);
        }
    }
private:
    OneKnobVocalAudioProcessor& mProcessor;
    juce::Slider editorSliders[Deesser::effectParameters::kNumOfParameters];
    juce::Label editorLabels[Deesser::effectParameters::kNumOfParameters];
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> sliderAttachments[Deesser::effectParameters::kNumOfParameters];
    juce::TextButton flipToggleButtons[Deesser::effectParameters::kNumOfParameters];

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DeEsserEditor);

};
