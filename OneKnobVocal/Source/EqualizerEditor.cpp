/*
  ==============================================================================

    EqualizerEditor.cpp
    Created: 6 Feb 2022 4:51:05pm
    Author:  yinsile

  ==============================================================================
*/

#include "EqualizerEditor.h"

EqualizerEditor::EqualizerEditor(OneKnobVocalAudioProcessor& p)
    :AudioProcessorEditor(&p), mProcessor(p)
{
    VolumeKnob.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    VolumeKnob.setTextBoxStyle(juce::Slider::TextBoxRight, true, 40, 20);
    addAndMakeVisible(VolumeKnob);
    VolumeKnobAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(mProcessor.apvts, "EQ_POST_GAIN", VolumeKnob);
    VolumeKnob.setBounds(0, 40, 120, 20);
}

EqualizerEditor::~EqualizerEditor()
{

}

void EqualizerEditor::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::seagreen);

    g.setColour(juce::Colours::white);
    g.setFont(15.0f);
    g.drawFittedText("Equalizer", getLocalBounds(), juce::Justification::centredTop, 1);
}