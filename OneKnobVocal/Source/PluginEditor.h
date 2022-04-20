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
#include "VerticalMeter.h"

//==============================================================================
/**
*/
class OneKnobVocalAudioProcessorEditor  : public juce::AudioProcessorEditor, public juce::Timer,
    public juce::ChangeListener
{
public:
    OneKnobVocalAudioProcessorEditor (OneKnobVocalAudioProcessor&);
    ~OneKnobVocalAudioProcessorEditor() override;

    //==============================================================================
    void timerCallback() override;
    void paint (juce::Graphics&) override;
    void resized() override;

    void changeListenerCallback(juce::ChangeBroadcaster* source)
    {
        updateRanges();
    }

    void updateRanges()
    {
        mGateEditor->updateRanges();
        mGateEditor->setAllButtonState();

        mDeEsserEditor->updateRanges();
        mDeEsserEditor->setAllButtonState();

        mEqualizerEditor->updateRanges();
        mEqualizerEditor->setAllButtonState();

        mCompressorEditor->updateRanges();
        mCompressorEditor->setAllButtonState();

        mSaturatorEditor->updateRanges();
        mSaturatorEditor->setAllButtonState();

        mReverbEditor->updateRanges();
        mReverbEditor->setAllButtonState();
    }

    // Alison: Toggle for main vs advanced setting switch
    //==============================================================================
    void changeToggleStateOnClick(juce::Button* button)
    {
        auto state = button->getToggleState();
        juce::String selectedString = state ? "Advanced" : "Basic";

        button->setButtonText(selectedString);
        
        if (selectedString == "Advanced")
        {
            addAndMakeVisible(mGateEditor.get());
            addAndMakeVisible(mDeEsserEditor.get());
            addAndMakeVisible(mEqualizerEditor.get());
            addAndMakeVisible(mCompressorEditor.get());
            addAndMakeVisible(mSaturatorEditor.get());
            addAndMakeVisible(mReverbEditor.get());
            mOneKnobSlider.setVisible(false);
        }
        else
        {
            addAndMakeVisible(mOneKnobSlider);
            mGateEditor.get()->setVisible(false);
            mDeEsserEditor.get()->setVisible(false);
            mEqualizerEditor.get()->setVisible(false);
            mCompressorEditor.get()->setVisible(false);
            mSaturatorEditor.get()->setVisible(false);
            mReverbEditor.get()->setVisible(false);
        }

        
    }

    // void updateToggleStateFromProcessor(juce::Button* button, juce::String id)
    // {
    //     // auto state = mProcessor.mappingRangeFlip[id];
    //     button->setToggleState(state, juce::dontSendNotification);
    //     juce::String selectedString = state ? "Advanced" : "Basic";
    //     button->setButtonText(selectedString);
    // }
    //==============================================================================

private:
    VerticalMeter mMeterInLeft, mMeterInRight, mMeterOutLeft, mMeterOutRight;
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    OneKnobVocalAudioProcessor& audioProcessor;

    juce::LookAndFeel_V4 royalTheme;
    juce::Colour backgroundColor = juce::Colour(0xff0f0038); //dark purple
    juce::Colour textColor = juce::Colour(0xffc2b948); // gold
    juce::Colour darkGold = juce::Colour(0xff423E12);
    juce::Colour lightPurple = juce::Colour(0xff6B43E0);
    juce::Colour clear = juce::Colour(0x00000000);
    
    juce::Slider mOneKnobSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> OneKnobAttach;
    juce::TextButton viewToggleButtons;

    std::unique_ptr<GateEditor> mGateEditor;
    std::unique_ptr<DeEsserEditor> mDeEsserEditor;
    std::unique_ptr<EqualizerEditor> mEqualizerEditor;
    std::unique_ptr<CompressorEditor> mCompressorEditor;
    std::unique_ptr<SaturatorEditor> mSaturatorEditor;
    std::unique_ptr<ReverbEditor> mReverbEditor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OneKnobVocalAudioProcessorEditor)
};
