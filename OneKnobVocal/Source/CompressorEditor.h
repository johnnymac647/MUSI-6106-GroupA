/*
  ==============================================================================

    CompressorEditor.h
    Created: 6 Feb 2022 4:50:44pm
    Author:  yinsile

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "PluginProcessor.h"

class CompressorEditor : public juce::AudioProcessorEditor
{
public:
    CompressorEditor(OneKnobVocalAudioProcessor&);
    ~CompressorEditor();
    void paint(juce::Graphics&) override;
private:
    OneKnobVocalAudioProcessor& mProcessor;
    
    
    juce::Slider InputGainKnob;
    juce::Slider ThresholdKnob;
    juce::Slider AttackKnob;
    juce::Slider ReleaseKnob;
    juce::Slider RatioKnob;
    juce::Slider MakeUpGainKnob;
    juce::Slider OutputGainKnob;
    
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> InputGainKnobAttach;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> ThresholdKnobAttach;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> AttackKnobAttach;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> ReleaseKnobAttach;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> RatioKnobAttach;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> MakeUpGainKnobAttach;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> OutputGainKnobAttach;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CompressorEditor);
};
