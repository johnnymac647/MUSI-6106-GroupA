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
    
    mMeterInLeft.setBounds(0, 0, 200, 15); //x, y, width, height
    mMeterInRight.setBounds(0, 20, 200, 15);
    mMeterOutLeft.setBounds(0, 40, 200, 15);
    mMeterOutRight.setBounds(0, 60, 200, 15);
    
    addAndMakeVisible(mMeterInLeft);
    addAndMakeVisible(mMeterInRight);
    addAndMakeVisible(mMeterOutLeft);
    addAndMakeVisible(mMeterOutRight);
    
    audioProcessor.loadedPreset.addChangeListener(this);

    mGateEditor = std::make_unique<GateEditor>(p);
    mGateEditor->setSize(133, 400);
    mGateEditor->setTopLeftPosition(0, 100);
    addAndMakeVisible(mGateEditor.get());

    mDeEsserEditor = std::make_unique<DeEsserEditor>(p);
    mDeEsserEditor->setSize(134, 600);
    mDeEsserEditor->setTopLeftPosition(133, 100);
    addAndMakeVisible(mDeEsserEditor.get());

    mEqualizerEditor = std::make_unique<EqualizerEditor>(p);
    mEqualizerEditor->setSize(133, 600);
    mEqualizerEditor->setTopLeftPosition(267, 100);
    addAndMakeVisible(mEqualizerEditor.get());

    mCompressorEditor = std::make_unique<CompressorEditor>(p);
    mCompressorEditor->setSize(133, 600);
    mCompressorEditor->setTopLeftPosition(400, 100);
    addAndMakeVisible(mCompressorEditor.get());

    mSaturatorEditor = std::make_unique<SaturatorEditor>(p);
    mSaturatorEditor->setSize(134, 600);
    mSaturatorEditor->setTopLeftPosition(533, 100);
    addAndMakeVisible(mSaturatorEditor.get());

    mReverbEditor = std::make_unique<ReverbEditor>(p);
    mReverbEditor->setSize(133, 600);
    mReverbEditor->setTopLeftPosition(667, 100);
    addAndMakeVisible(mReverbEditor.get());

    mOneKnobSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mOneKnobSlider.setRange(0, 1);
    mOneKnobSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 80, 20);
    mOneKnobSlider.setBounds(0, 550, 120, 120);
    OneKnobAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "ONE_KNOB", mOneKnobSlider);
    addAndMakeVisible(mOneKnobSlider);

    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (800, 700);
    
    startTimerHz(24); //refresh the meter at the rate of 24Hz
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
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void OneKnobVocalAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
