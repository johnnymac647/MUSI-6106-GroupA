/*
  ==============================================================================

    CompressorEditor.cpp
    Created: 6 Feb 2022 4:50:44pm
    Author:  yinsile

  ==============================================================================
*/

#include "CompressorEditor.h"

CompressorEditor::CompressorEditor(Compressor& p)
    :AudioProcessorEditor(&p), mProcessor(p)
{
    VolumeKnob.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    VolumeKnob.setTextBoxStyle(juce::Slider::TextBoxRight, true, 40, 20);
    addAndMakeVisible(VolumeKnob);
    VolumeKnobAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(*(mProcessor.ptr_apvts), "COMPRESSOR_POST_GAIN", VolumeKnob);
    VolumeKnob.setBounds(0, 40, 120, 20);
}
CompressorEditor::~CompressorEditor()
{

}
void CompressorEditor::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::plum);

    g.setColour(juce::Colours::white);
    g.setFont(15.0f);
    g.drawFittedText("Compressor", getLocalBounds(), juce::Justification::centredTop, 1);
}