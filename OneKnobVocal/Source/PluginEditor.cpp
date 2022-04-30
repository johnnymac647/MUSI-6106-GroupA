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
#include "Gate.h"
#include "Reverb.h"
#include "Saturator.h"

//==============================================================================
OneKnobVocalAudioProcessorEditor::OneKnobVocalAudioProcessorEditor (OneKnobVocalAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    audioProcessor.isEditorOpen = true;


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


    OneKnobAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "ONE_KNOB", mOneKnobSlider);
    mOneKnobSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mOneKnobSlider.setRange(0, 1);
    mOneKnobSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 10);
    mOneKnobSlider.setBounds(0, 650, 120, 120);

    royalTheme.setColour(juce::Slider::thumbColourId, textColor);
    royalTheme.setColour(juce::Slider::textBoxTextColourId, textColor);
    royalTheme.setColour(juce::Slider::rotarySliderFillColourId, textColor);
    royalTheme.setColour(juce::Slider::rotarySliderOutlineColourId, darkGold);
    royalTheme.setColour(juce::Slider::textBoxOutlineColourId, clear);
    
    mOneKnobSlider.setLookAndFeel(&royalTheme);



    mainDropdownBox.setBounds(280, 40, 160, 20);
    addAndMakeVisible(mainDropdownBox);
    mainDropdownBox.addItem("Default", kDefault);
    mainDropdownBox.addItem("Club", kClub);
    mainDropdownBox.addItem("Country", kCountry);
    mainDropdownBox.addItem("Pop", kPop);
    mainDropdownBox.addItem("Rock", kRock);
    mainDropdownBox.addItem("Select Custom...", kCustomSelect);
    mainDropdownBox.setSelectedId(audioProcessor.selectedComboBoxID);
    mainDropdownBox.setTextWhenNothingSelected(audioProcessor.selectedComboBoxMessage);

    mainDropdownBox.onChange = [this] {
        if (!isLoadingStateInformation)
            loadPreset();
    };

    savePresetButton.setBounds(460, 40, 60, 20);
    addAndMakeVisible(savePresetButton);



    savePresetButton.onClick = [&]
    {
        savePreset();
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
    audioProcessor.loadedApvts.addChangeListener(this);
    audioProcessor.loadedStateInformation.addChangeListener(this);
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.

    setSize (800, 750);
}



OneKnobVocalAudioProcessorEditor::~OneKnobVocalAudioProcessorEditor()
{
    audioProcessor.isEditorOpen = false;
    audioProcessor.loadedPreset.removeChangeListener(this);
    audioProcessor.loadedApvts.removeChangeListener(this);
    audioProcessor.loadedStateInformation.removeChangeListener(this);
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

void OneKnobVocalAudioProcessorEditor::changeListenerCallback(juce::ChangeBroadcaster* source)
{
    if (source == &audioProcessor.loadedPreset)
    {
        removeAsSliderListener();
        updateRanges();
    }
    else if (source == &audioProcessor.loadedApvts)
    {
        addAsSliderListener();
    }
    else if (source == &audioProcessor.loadedStateInformation)
    {
        isLoadingStateInformation = true;
        removeAsSliderListener();
        updateRanges();
        mainDropdownBox.setSelectedId(audioProcessor.selectedComboBoxID);
        if (!audioProcessor.selectedComboBoxID)
        {
            mainDropdownBox.setTextWhenNoChoicesAvailable(audioProcessor.selectedComboBoxMessage);
        }
        isLoadingStateInformation = false;
    }
}

void OneKnobVocalAudioProcessorEditor::addAsSliderListener()
{
    mGateEditor->addSliderListeners(this);
    mDeEsserEditor->addSliderListeners(this);
    mEqualizerEditor->addSliderListeners(this);
    mCompressorEditor->addSliderListeners(this);
    mSaturatorEditor->addSliderListeners(this);
    mReverbEditor->addSliderListeners(this);
}

void OneKnobVocalAudioProcessorEditor::removeAsSliderListener()
{
    mGateEditor->removeSliderListeners(this);
    mDeEsserEditor->removeSliderListeners(this);
    mEqualizerEditor->removeSliderListeners(this);
    mCompressorEditor->removeSliderListeners(this);
    mSaturatorEditor->removeSliderListeners(this);
    mReverbEditor->removeSliderListeners(this);
}

void OneKnobVocalAudioProcessorEditor::sliderValueChanged(juce::Slider* slider)
{
    if (mainDropdownBox.getSelectedId())
    {
        audioProcessor.selectedComboBoxMessage = mainDropdownBox.getText() + "(Modified)";
        audioProcessor.selectedComboBoxID = 0;
        mainDropdownBox.setTextWhenNothingSelected(mainDropdownBox.getText() + "(Modified)");
        mainDropdownBox.setSelectedId(0);
    }
}

void OneKnobVocalAudioProcessorEditor::updateRanges()
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

void OneKnobVocalAudioProcessorEditor::changeToggleStateOnClick(juce::Button* button)
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

void OneKnobVocalAudioProcessorEditor::savePreset()
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
                audioProcessor.savePluginPreset(dataToSave);


                fileToSave.replaceWithData(dataToSave.getData(), dataToSave.getSize());
            }
        });
}

void OneKnobVocalAudioProcessorEditor::loadPreset()
{
    switch (mainDropdownBox.getSelectedId())
    {
    case kDefault:
        audioProcessor.loadSavedPreset(BinaryData::Default_pst, BinaryData::Default_pstSize);
        audioProcessor.selectedComboBoxID = kDefault;
        audioProcessor.selectedComboBoxMessage = mainDropdownBox.getText();
        break;
    case kClub:
        audioProcessor.loadSavedPreset(BinaryData::Club_pst, BinaryData::Club_pstSize);
        audioProcessor.selectedComboBoxID = kClub;
        audioProcessor.selectedComboBoxMessage = mainDropdownBox.getText();
        break;
    case kCountry:
        audioProcessor.loadSavedPreset(BinaryData::Country_pst, BinaryData::Country_pstSize);
        audioProcessor.selectedComboBoxID = kCountry;
        audioProcessor.selectedComboBoxMessage = mainDropdownBox.getText();
        break;
    case kPop:
        audioProcessor.loadSavedPreset(BinaryData::Pop_pst, BinaryData::Pop_pstSize);
        audioProcessor.selectedComboBoxID = kPop;
        audioProcessor.selectedComboBoxMessage = mainDropdownBox.getText();
        break;
    case kRock:
        audioProcessor.loadSavedPreset(BinaryData::Rock_pst, BinaryData::Rock_pstSize);
        audioProcessor.selectedComboBoxID = kRock;
        audioProcessor.selectedComboBoxMessage = mainDropdownBox.getText();
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

                    audioProcessor.loadSavedPreset(dataToLoad.getData(), dataToLoad.getSize());
                }
                mainDropdownBox.setTextWhenNothingSelected("Custom");
            });
        mainDropdownBox.setSelectedId(0);
        audioProcessor.selectedComboBoxID = 0;
        audioProcessor.selectedComboBoxMessage = "Custom";
        break;
    }
    default:
        break;
    }
}
