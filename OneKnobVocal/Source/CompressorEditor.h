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
    juce::Slider VolumeKnob;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> VolumeKnobAttach;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CompressorEditor);
};