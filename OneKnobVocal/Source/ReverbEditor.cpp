/*
  ==============================================================================

    ReverbEditor.cpp
    Created: 6 Feb 2022 4:51:25pm
    Author:  yinsile

  ==============================================================================
*/

#include "ReverbEditor.h"

ReverbEditor::ReverbEditor(Reverb& p)
    :AudioProcessorEditor(&p), mProcessor(p)
{
    VolumeKnob.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    VolumeKnob.setTextBoxStyle(juce::Slider::TextBoxRight, true, 40, 20);
    addAndMakeVisible(VolumeKnob);
    VolumeKnobAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(mProcessor.apvts, "GAIN", VolumeKnob);
    VolumeKnob.setBounds(0, 40, 120, 20);
}
ReverbEditor::~ReverbEditor()
{

}
void ReverbEditor::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::silver);

    g.setColour(juce::Colours::white);
    g.setFont(15.0f);
    g.drawFittedText("Reverb", getLocalBounds(), juce::Justification::centredTop, 1);
}