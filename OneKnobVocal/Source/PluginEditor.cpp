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
    mInputGainSlider = std::make_unique<GainSlider>(dynamic_cast<Gain&>(*audioProcessor.inputGainNode->getProcessor()));
    mInputGainSlider->setSize(400, 50);
    mInputGainSlider->setTopLeftPosition(0, 0);
    addAndMakeVisible(mInputGainSlider.get());

    mGateEditor = std::make_unique<GateEditor>(dynamic_cast<Gate&>(*audioProcessor.gateNode->getProcessor()));
    mGateEditor->setSize(133, 550);
    mGateEditor->setTopLeftPosition(0, 50);
    addAndMakeVisible(mGateEditor.get());

    mDeEsserEditor = std::make_unique<DeEsserEditor>(dynamic_cast<Deesser&>(*audioProcessor.deEsserNode->getProcessor()));
    mDeEsserEditor->setSize(134, 550);
    mDeEsserEditor->setTopLeftPosition(133, 50);
    addAndMakeVisible(mDeEsserEditor.get());

    mEqualizerEditor = std::make_unique<EqualizerEditor>(dynamic_cast<Equalizer&>(*audioProcessor.equalizerNode->getProcessor()));
    mEqualizerEditor->setSize(133, 550);
    mEqualizerEditor->setTopLeftPosition(267, 50);
    addAndMakeVisible(mEqualizerEditor.get());

    mCompressorEditor = std::make_unique<CompressorEditor>(dynamic_cast<Compressor&>(*audioProcessor.compressorNode->getProcessor()));
    mCompressorEditor->setSize(133, 550);
    mCompressorEditor->setTopLeftPosition(400, 50);
    addAndMakeVisible(mCompressorEditor.get());

    mSaturatorEditor = std::make_unique<SaturatorEditor>(dynamic_cast<Saturator&>(*audioProcessor.saturatorNode->getProcessor()));
    mSaturatorEditor->setSize(134, 550);
    mSaturatorEditor->setTopLeftPosition(533, 50);
    addAndMakeVisible(mSaturatorEditor.get());

    mReverbEditor = std::make_unique<ReverbEditor>(dynamic_cast<Reverb&>(*audioProcessor.reverbNode->getProcessor()));
    mReverbEditor->setSize(133, 550);
    mReverbEditor->setTopLeftPosition(667, 50);
    addAndMakeVisible(mReverbEditor.get());

    mOutputGainSlider = std::make_unique<GainSlider>(dynamic_cast<Gain&>(*audioProcessor.outputGainNode->getProcessor()), juce::Colours::cyan);
    mOutputGainSlider->setSize(400, 50);
    mOutputGainSlider->setTopLeftPosition(400, 0);
    addAndMakeVisible(mOutputGainSlider.get());
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
