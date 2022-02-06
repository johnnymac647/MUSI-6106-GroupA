/*
  ==============================================================================

    GainSlider.cpp
    Created: 6 Feb 2022 4:00:42pm
    Author:  yinsile

  ==============================================================================
*/

#include "GainSlider.h"

GainSlider::GainSlider(Gain& p, juce::Colour c)
    :AudioProcessorEditor(&p), mProcessor(p)
{
    mBackgroundColour = c;
    VolumeKnob.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    VolumeKnob.setTextBoxStyle(juce::Slider::TextBoxRight, true, 40, 20);
    addAndMakeVisible(VolumeKnob);
    VolumeKnobAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(mProcessor.apvts, "GAIN", VolumeKnob);
    VolumeKnob.setBounds(200, 15, 160, 20);
}

GainSlider::~GainSlider()
{

}

void GainSlider::paint(juce::Graphics& g)
{
    g.fillAll(mBackgroundColour);
}