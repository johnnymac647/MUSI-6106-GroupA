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



    inline static juce::Font savoyeItalic{juce::Font(juce::Typeface::createSystemTypefaceFor(BinaryData::Savoye_Regular_ttf, BinaryData::Savoye_Regular_ttfSize ))};

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

    RangeDisplay mainTooltip{ this };

    void changeListenerCallback(juce::ChangeBroadcaster* source) override
    {
        if (source == &audioProcessor.loadedPreset)
        {
            removeAsSliderListener();
            updateRanges();
        }
        else if (source == &audioProcessor.loadedApvts)
            addAsSliderListener();
    }

    void addAsSliderListener()
    {
        mGateEditor->addSliderListeners(this);
        mDeEsserEditor->addSliderListeners(this);
        mEqualizerEditor->addSliderListeners(this);
        mCompressorEditor->addSliderListeners(this);
        mSaturatorEditor->addSliderListeners(this);
        mReverbEditor->addSliderListeners(this);
    }

    void removeAsSliderListener()
    {
        mGateEditor->removeSliderListeners(this);
        mDeEsserEditor->removeSliderListeners(this);
        mEqualizerEditor->removeSliderListeners(this);
        mCompressorEditor->removeSliderListeners(this);
        mSaturatorEditor->removeSliderListeners(this);
        mReverbEditor->removeSliderListeners(this);
    }

    void sliderValueChanged(juce::Slider* slider) override
    {
        if (mainDropdownBox.getSelectedId())
        {
            mainDropdownBox.setTextWhenNothingSelected(mainDropdownBox.getText()+"(Modified)");
            mainDropdownBox.setSelectedId(0);
        }
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

        audioProcessor.setAudioParameters();
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

    void savePreset()
    {
        myChooser = std::make_unique<juce::FileChooser>("Saving Presets..",
            juce::File::getSpecialLocation(juce::File::userHomeDirectory),
            "*.pst");

        auto folderChooserFlags = juce::FileBrowserComponent::saveMode | juce::FileBrowserComponent::canSelectFiles | juce::FileBrowserComponent::warnAboutOverwriting;
        myChooser->launchAsync(folderChooserFlags, [this](const juce::FileChooser& chooser)
            {
                juce::File fileToSave(chooser.getResult());


                if (fileToSave.getFullPathName() != "")
                {
                    juce::MemoryBlock dataToSave;
                    audioProcessor.getStateInformation(dataToSave);


                    fileToSave.replaceWithData(dataToSave.getData(), dataToSave.getSize());
                }
            });
    }

    void loadPreset()
    {
        switch (mainDropdownBox.getSelectedId())
        {
        case kDefault:
            audioProcessor.setStateInformation(BinaryData::Default_pst, BinaryData::Default_pstSize);
            break;
        case kClub:
            audioProcessor.setStateInformation(BinaryData::Club_pst, BinaryData::Club_pstSize);
            break;
        case kCountry:
            audioProcessor.setStateInformation(BinaryData::Country_pst, BinaryData::Country_pstSize);
            break;
        case kPop:
            audioProcessor.setStateInformation(BinaryData::Pop_pst, BinaryData::Pop_pstSize);
            break;
        case kRock:
            audioProcessor.setStateInformation(BinaryData::Rock_pst, BinaryData::Rock_pstSize);
            break;
        case kCustomSelect:
        {
            myChooser = std::make_unique<juce::FileChooser>("Loading Custom Presets..",
                juce::File::getSpecialLocation(juce::File::userHomeDirectory),
                "*.pst");

            auto folderChooserFlags = juce::FileBrowserComponent::openMode | juce::FileBrowserComponent::canSelectFiles;
            myChooser->launchAsync(folderChooserFlags, [this](const juce::FileChooser& chooser)
                {
                    juce::File fileToLoad(chooser.getResult());


                    if (fileToLoad.getFullPathName() != "")
                    {
                        juce::MemoryBlock dataToLoad;
                        fileToLoad.loadFileAsData(dataToLoad);

                        audioProcessor.setStateInformation(dataToLoad.getData(), dataToLoad.getSize());
                    }
                    mainDropdownBox.setTextWhenNothingSelected("Custom");
                });
            mainDropdownBox.setSelectedId(0);
            break;
        }
        default:
            break;
        }
    }

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OneKnobVocalAudioProcessorEditor)
};
