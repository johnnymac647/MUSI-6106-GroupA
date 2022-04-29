/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "Compressor.h"
#include "DeEsser.h"
#include "Equalizer.h"
#include "Gain.h"
#include "Gate.h"
#include "Reverb.h"
#include "Saturator.h"

//==============================================================================
OneKnobVocalAudioProcessorEditor::OneKnobVocalAudioProcessorEditor (OneKnobVocalAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    audioProcessor.isEditorOpen = true;


    mainDropdownBox.setBounds(280, 40, 160, 20);
    addAndMakeVisible(mainDropdownBox);
    mainDropdownBox.addItem("Default", kDefault);
    mainDropdownBox.addItem("Club", kClub);
    mainDropdownBox.addItem("Country", kCountry);
    mainDropdownBox.addItem("Pop", kPop);
    mainDropdownBox.addItem("Rock", kRock);
    mainDropdownBox.addItem("Select Custom...", kCustomSelect);
    mainDropdownBox.setTextWhenNothingSelected("Custom");

    mainDropdownBox.onChange = [this] { 
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
                });
            mainDropdownBox.setSelectedId(0);
            break;
        }
        default:
            break;
        }
    };
    mainDropdownBox.setSelectedId(kDefault);

    savePresetButton.setBounds(460, 40, 60, 20);
    addAndMakeVisible(savePresetButton);



    savePresetButton.onClick = [&]
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
    };



    // Alison: Toggle implement for switch between main vs advanced setting GUI
    //==============================================================================
    viewToggleButtons.setClickingTogglesState(true);
    viewToggleButtons.setBounds(650, 650, 120, 60);
    viewToggleButtons.setButtonText("Basic");
    viewToggleButtons.onClick = [this] { changeToggleStateOnClick(&viewToggleButtons); };
    addAndMakeVisible(viewToggleButtons);
    viewToggleButtons.setAlwaysOnTop(true);
    addAndMakeVisible(mOneKnobSlider);
    //==============================================================================
    
    mMeterInLeft.setBounds(20, 20, 20, 150); //x, y, width, height
    mMeterInRight.setBounds(60, 20, 20, 150);
    mMeterOutLeft.setBounds(720, 20, 20, 150);
    mMeterOutRight.setBounds(760, 20, 20, 150);
    
    addAndMakeVisible(mMeterInLeft);
    addAndMakeVisible(mMeterInRight);
    addAndMakeVisible(mMeterOutLeft);
    addAndMakeVisible(mMeterOutRight);
    
    startTimerHz(24); //refresh the meter at the rate of 24Hz
    
    audioProcessor.loadedPreset.addChangeListener(this);

    mGateEditor = std::make_unique<GateEditor>(p);
    mGateEditor->setSize(133, 600); // (133, 400)
    mGateEditor->setTopLeftPosition(0, 200);

    mDeEsserEditor = std::make_unique<DeEsserEditor>(p);
    mDeEsserEditor->setSize(134, 600);
    mDeEsserEditor->setTopLeftPosition(133, 200);

    mEqualizerEditor = std::make_unique<EqualizerEditor>(p);
    mEqualizerEditor->setSize(133, 600);
    mEqualizerEditor->setTopLeftPosition(267, 200);

    mCompressorEditor = std::make_unique<CompressorEditor>(p);
    mCompressorEditor->setSize(133, 600);
    mCompressorEditor->setTopLeftPosition(400, 200);

    mSaturatorEditor = std::make_unique<SaturatorEditor>(p);
    mSaturatorEditor->setSize(134, 600);
    mSaturatorEditor->setTopLeftPosition(533, 200);

    mReverbEditor = std::make_unique<ReverbEditor>(p);
    mReverbEditor->setSize(133, 600);
    mReverbEditor->setTopLeftPosition(667, 200);

    mOneKnobSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mOneKnobSlider.setRange(0, 1);
    mOneKnobSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 10);
    mOneKnobSlider.setBounds(0, 650, 120, 120);
    OneKnobAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "ONE_KNOB", mOneKnobSlider);

    royalTheme.setColour(juce::Slider::thumbColourId, textColor);
    royalTheme.setColour(juce::Slider::textBoxTextColourId, textColor);
    royalTheme.setColour(juce::Slider::rotarySliderFillColourId, textColor);
    royalTheme.setColour(juce::Slider::rotarySliderOutlineColourId, darkGold);
    royalTheme.setColour(juce::Slider::textBoxOutlineColourId, clear);
    
    mOneKnobSlider.setLookAndFeel(&royalTheme);


    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (800, 750);
    
}



OneKnobVocalAudioProcessorEditor::~OneKnobVocalAudioProcessorEditor()
{
    audioProcessor.isEditorOpen = false;
}

//==============================================================================


void OneKnobVocalAudioProcessorEditor::timerCallback()
{
    float fInLevelLeft = audioProcessor.getRmsValue(0, 0);
    float fInLevelRight = audioProcessor.getRmsValue(1, 0);
    float fOutLevelLeft = audioProcessor.getRmsValue(0, 1);
    float fOutLevelRight = audioProcessor.getRmsValue(1, 1);
    
    
    mMeterInLeft.setLevel(fInLevelLeft);
    mMeterInRight.setLevel(fInLevelRight);
    mMeterOutLeft.setLevel(fOutLevelLeft);
    mMeterOutRight.setLevel(fOutLevelRight);
    
    mMeterInLeft.repaint();
    mMeterInRight.repaint();
    mMeterOutLeft.repaint();
    mMeterOutRight.repaint();
}


void OneKnobVocalAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (backgroundColor);
    g.setColour(textColor);
    g.setFont(savoyeItalic.withHeight(100.0f));
    g.drawText("Voce Dolce", getWidth()/2 - 200, 110, 400, 20, juce::Justification::centred, true);

}

void OneKnobVocalAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    auto sliderWidth = 380;
    mOneKnobSlider.setBounds ((getWidth() - sliderWidth)/2, (getHeight() - sliderWidth)/2 + 50, sliderWidth, sliderWidth);
}
