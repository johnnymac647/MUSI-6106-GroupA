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

    mGateEditor = std::make_unique<GateEditor>(p);
    mGateEditor->setSize(133, 400);
    mGateEditor->setTopLeftPosition(0, 0);
    addAndMakeVisible(mGateEditor.get());

    mDeEsserEditor = std::make_unique<DeEsserEditor>(p);
    mDeEsserEditor->setSize(134, 600);
    mDeEsserEditor->setTopLeftPosition(133, 0);
    addAndMakeVisible(mDeEsserEditor.get());

    mEqualizerEditor = std::make_unique<EqualizerEditor>(p);
    mEqualizerEditor->setSize(133, 600);
    mEqualizerEditor->setTopLeftPosition(267, 0);
    addAndMakeVisible(mEqualizerEditor.get());

    mCompressorEditor = std::make_unique<CompressorEditor>(p);
    mCompressorEditor->setSize(133, 600);
    mCompressorEditor->setTopLeftPosition(400, 0);
    addAndMakeVisible(mCompressorEditor.get());

    mSaturatorEditor = std::make_unique<SaturatorEditor>(p);
    mSaturatorEditor->setSize(134, 600);
    mSaturatorEditor->setTopLeftPosition(533, 0);
    addAndMakeVisible(mSaturatorEditor.get());

    mReverbEditor = std::make_unique<ReverbEditor>(p);
    mReverbEditor->setSize(133, 600);
    mReverbEditor->setTopLeftPosition(667, 0);
    addAndMakeVisible(mReverbEditor.get());

    mOneKnobSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mOneKnobSlider.setRange(0, 1);
    mOneKnobSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 80, 20);
    mOneKnobSlider.setBounds(0, 450, 120, 120);
    mOneKnobSlider.addListener(this);
    OneKnobAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "ONE_KNOB", mOneKnobSlider);
    addAndMakeVisible(mOneKnobSlider);

    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (800, 600);
}

OneKnobVocalAudioProcessorEditor::~OneKnobVocalAudioProcessorEditor()
{
}

//==============================================================================
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

void OneKnobVocalAudioProcessorEditor::sliderValueChanged(juce::Slider* slider)
{
    if (slider == &mOneKnobSlider)
    {
        mGateEditor->oneKnobMapping(mOneKnobSlider.getValue());
    }
}