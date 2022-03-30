/*
  ==============================================================================

    EqualizerEditor.h
    Created: 6 Feb 2022 4:51:05pm
    Author:  yinsile

  ==============================================================================
*/

#pragma once
#include "PluginProcessor.h"
#include "ModdedNormalisableRange.h"
#include "Equalizer.h"

class EqualizerEditor : public juce::AudioProcessorEditor,
    public juce::Slider::Listener
{
public:
    EqualizerEditor(OneKnobVocalAudioProcessor&);
    ~EqualizerEditor() override;
    void paint(juce::Graphics&) override;
    void sliderValueChanged(juce::Slider* slider) override;
    void updateRanges();

    void changeToggleStateOnClick(juce::Button* button)
    {
        auto state = button->getToggleState();
        juce::String selectedString = state ? "-" : "+";

        button->setButtonText(selectedString);

        for (int i = 0; i < Equalizer::effectParameters::kNumOfParameters; i++)
        {
            if (button == &flipToggleButtons[i])
            {
                mProcessor.mappingRangeFlip.set(Equalizer::parameterIDs[i], state);
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
        for (int i = 0; i < Equalizer::effectParameters::kNumOfParameters; i++)
        {
            updateToggleStateFromProcessor(&flipToggleButtons[i], Equalizer::parameterIDs[i]);
        }
    }
private:
    OneKnobVocalAudioProcessor& mProcessor;

    juce::Slider editorSliders[Equalizer::effectParameters::kNumOfParameters];
    juce::Label editorLabels[Equalizer::effectParameters::kNumOfParameters];
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> sliderAttachments[Equalizer::effectParameters::kNumOfParameters];
    juce::TextButton flipToggleButtons[Equalizer::effectParameters::kNumOfParameters];

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(EqualizerEditor);
};
