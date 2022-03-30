/*
  ==============================================================================

    CompressorEditor.h
    Created: 6 Feb 2022 4:50:44pm
    Author:  yinsile

  ==============================================================================
*/

#pragma once
#include "PluginProcessor.h"
#include "ModdedNormalisableRange.h"
#include "Compressor.h" 

class CompressorEditor : public juce::AudioProcessorEditor,
    public juce::Slider::Listener
{
public:
    CompressorEditor(OneKnobVocalAudioProcessor&);
    ~CompressorEditor();
    void paint(juce::Graphics&) override;
    void sliderValueChanged(juce::Slider* slider) override;
    void updateRanges();
    void changeToggleStateOnClick(juce::Button* button)
    {
        auto state = button->getToggleState();
        juce::String selectedString = state ? "-" : "+";

        button->setButtonText(selectedString);

        for (int i = 0; i < Compressor::effectParameters::kNumOfParameters; i++)
        {
            if (button == &flipToggleButtons[i])
            {
                mProcessor.mappingRangeFlip.set(Compressor::parameterIDs[i], state);
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
        for (int i = 0; i < Compressor::effectParameters::kNumOfParameters; i++)
        {
            updateToggleStateFromProcessor(&flipToggleButtons[i], Compressor::parameterIDs[i]);
        }
    }
private:
    OneKnobVocalAudioProcessor& mProcessor;
    
    juce::Slider editorSliders[Compressor::effectParameters::kNumOfParameters];
    juce::Label editorLabels[Compressor::effectParameters::kNumOfParameters];
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> sliderAttachments[Compressor::effectParameters::kNumOfParameters];
    juce::TextButton flipToggleButtons[Compressor::effectParameters::kNumOfParameters];
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CompressorEditor);
};
