/*
  ==============================================================================

    SaturatorEditor.cpp
    Created: 6 Feb 2022 4:51:40pm
    Author:  yinsile

  ==============================================================================
*/

#include "SaturatorEditor.h"

SaturatorEditor::SaturatorEditor(OneKnobVocalAudioProcessor& p)
    :AudioProcessorEditor(&p), mProcessor(p)
{
    
    GainKnob.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    GainKnob.setTextBoxStyle(juce::Slider::TextBoxRight, true, 40, 20);
    addAndMakeVisible(GainKnob);
    GainKnobAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(mProcessor.apvts, "SATURATOR_PRE_GAIN", GainKnob);
    GainKnob.setBounds(0, 40, 120, 20);
    
    MixKnob.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    MixKnob.setTextBoxStyle(juce::Slider::TextBoxRight, true, 40, 20);
    addAndMakeVisible(MixKnob);
    MixKnobAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(mProcessor.apvts, "SATURATOR_MIX", MixKnob);
    MixKnob.setBounds(0, 65, 120, 20);

    
    VolumeKnob.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    VolumeKnob.setTextBoxStyle(juce::Slider::TextBoxRight, true, 40, 20);
    addAndMakeVisible(VolumeKnob);
    VolumeKnobAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(mProcessor.apvts, "SATURATOR_POST_GAIN", VolumeKnob);
    VolumeKnob.setBounds(0, 90, 120, 20);
    
    
}
SaturatorEditor::~SaturatorEditor()
{

}
void SaturatorEditor::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::darkgrey);

    g.setColour(juce::Colours::white);
    g.setFont(15.0f);
    g.drawFittedText("Saturator", getLocalBounds(), juce::Justification::centredTop, 1);
}
