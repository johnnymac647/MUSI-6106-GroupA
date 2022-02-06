/*
  ==============================================================================

    DeEsserEditor.cpp
    Created: 6 Feb 2022 4:50:53pm
    Author:  yinsile

  ==============================================================================
*/

#include "DeEsserEditor.h"

DeEsserEditor::DeEsserEditor(Deesser& p)
    :AudioProcessorEditor(&p), mProcessor(p)
{
    VolumeKnob.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    VolumeKnob.setTextBoxStyle(juce::Slider::TextBoxRight, true, 40, 20);
    addAndMakeVisible(VolumeKnob);
    VolumeKnobAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(mProcessor.apvts, "GAIN", VolumeKnob);
    VolumeKnob.setBounds(0, 40, 120, 20);
}

DeEsserEditor::~DeEsserEditor()
{

}

void DeEsserEditor::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::orchid);

    g.setColour(juce::Colours::white);
    g.setFont(15.0f);
    g.drawFittedText("De-Esser", getLocalBounds(), juce::Justification::centredTop, 1);
}