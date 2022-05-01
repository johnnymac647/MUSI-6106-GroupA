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
#include "RangeDisplay.h"

//==============================================================================
/**
*/
class OneKnobVocalAudioProcessorEditor  : public juce::AudioProcessorEditor, public juce::Timer,
    juce::ChangeListener, juce::Slider::Listener
{
public:
    enum kPresets
    {
        kDefault=1,
        kClub,
        kCountry,
        kPop,
        kRock,
        kCustomSelect
    };


    OneKnobVocalAudioProcessorEditor (OneKnobVocalAudioProcessor&);
    ~OneKnobVocalAudioProcessorEditor() override;

    //==============================================================================
    void timerCallback() override;
    void paint (juce::Graphics&) override;
    void resized() override;




private:
    VerticalMeter mMeterInLeft, mMeterInRight, mMeterOutLeft, mMeterOutRight;
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    OneKnobVocalAudioProcessor& audioProcessor;


#ifdef __APPLE__
    juce::Font savoyeItalic{"Savoye LET", "Regular", 100.f};
#else
    inline static juce::Font savoyeItalic{juce::Font(juce::Typeface::createSystemTypefaceFor(BinaryData::Savoye_Regular_ttf, BinaryData::Savoye_Regular_ttfSize ))};
#endif

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

    juce::ComboBox mainDropdownBox;

    juce::TextButton savePresetButton{"Save"};

    std::unique_ptr<juce::FileChooser> myChooser;

    bool isLoadingStateInformation = false;

    RangeDisplay mainTooltip{ this };

    void changeListenerCallback(juce::ChangeBroadcaster* source) override;

    void addAsSliderListener();

    void removeAsSliderListener();

    void sliderValueChanged(juce::Slider* slider) override;

    void updateRanges();

    void setAdvancedMode(bool b);

    // Alison: Toggle for main vs advanced setting switch
    //==============================================================================
    void changeToggleStateOnClick(juce::Button* button);

    void savePreset();

    void loadPreset();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OneKnobVocalAudioProcessorEditor)
};
