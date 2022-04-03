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
#include "Gate.h"

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

        for (int i = 0; i < Gate::effectParameters::kNumOfParameters; i++)
        {
            if (button == &flipToggleButtons[i])
            {
                mProcessor.mappingRangeFlip.set(Gate::parameterIDs[i], state);
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
        for (int i = 0; i < Gate::effectParameters::kNumOfParameters; i++)
        {
            updateToggleStateFromProcessor(&flipToggleButtons[i], Gate::parameterIDs[i]);
        }
    }

private:
    OneKnobVocalAudioProcessor& mProcessor;

    juce::Slider editorSliders[Gate::effectParameters::kNumOfParameters];
    juce::Label editorLabels[Gate::effectParameters::kNumOfParameters];
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> sliderAttachments[Gate::effectParameters::kNumOfParameters];
    juce::TextButton flipToggleButtons[Gate::effectParameters::kNumOfParameters];
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(GateEditor);
};
