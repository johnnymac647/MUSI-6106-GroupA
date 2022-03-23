/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "GateEditor.h"
#include "DeEsserEditor.h"
#include "EqualizerEditor.h"
#include "CompressorEditor.h"
#include "SaturatorEditor.h"
#include "ReverbEditor.h"

//==============================================================================
/**
*/
class OneKnobVocalAudioProcessorEditor  : public juce::AudioProcessorEditor,
    public juce::Slider::Listener
{
public:
    OneKnobVocalAudioProcessorEditor (OneKnobVocalAudioProcessor&);
    ~OneKnobVocalAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

    void sliderValueChanged(juce::Slider* slider) override;

    void updateRanges()
    {
        mGateEditor->updateRanges();
        mDeEsserEditor->updateRanges();
        mEqualizerEditor->updateRanges();
        mCompressorEditor->updateRanges();
        mSaturatorEditor->updateRanges();
        mReverbEditor->updateRanges();
    }

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    OneKnobVocalAudioProcessor& audioProcessor;


    juce::Slider mOneKnobSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> OneKnobAttach;

    std::unique_ptr<GateEditor> mGateEditor;
    std::unique_ptr<DeEsserEditor> mDeEsserEditor;
    std::unique_ptr<EqualizerEditor> mEqualizerEditor;
    std::unique_ptr<CompressorEditor> mCompressorEditor;
    std::unique_ptr<SaturatorEditor> mSaturatorEditor;
    std::unique_ptr<ReverbEditor> mReverbEditor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OneKnobVocalAudioProcessorEditor)
};
