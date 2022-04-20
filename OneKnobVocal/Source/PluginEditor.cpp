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
    // g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
    g.fillAll (backgroundColor);
    g.setColour(textColor);
    g.setFont(juce::Font("Savoye LET", 100.0f, juce::Font::italic));
    g.drawText("Voce Dolce", getWidth()/2 - 150, 110, 300, 20, juce::Justification::centred, true);

}

void OneKnobVocalAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    auto sliderWidth = 380;
    mOneKnobSlider.setBounds ((getWidth() - sliderWidth)/2, (getHeight() - sliderWidth)/2 + 50, sliderWidth, sliderWidth);
}
