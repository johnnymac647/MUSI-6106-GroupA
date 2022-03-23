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
    int i = 1;

    GainKnobLabel.setText("Pre Gain", juce::NotificationType::dontSendNotification);
    GainKnobLabel.setBounds(0, 20 * (i++), 120, 20);
    addAndMakeVisible(GainKnobLabel);

    GainKnob.setSliderStyle(juce::Slider::SliderStyle::ThreeValueHorizontal);
    GainKnob.setTextBoxStyle(juce::Slider::TextBoxRight, true, 40, 20);
    addAndMakeVisible(GainKnob);
    GainKnobAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(mProcessor.apvts, "SATURATOR_PRE_GAIN", GainKnob);
    GainKnob.addListener(this);
    GainKnob.setMinAndMaxValues(mProcessor.knobValueMap["SATURATOR_PRE_GAIN"].start, mProcessor.knobValueMap["SATURATOR_PRE_GAIN"].end);
    GainKnob.setBounds(0, 20 * (i++), 120, 20);

    MixKnobLabel.setText("Mix", juce::NotificationType::dontSendNotification);
    MixKnobLabel.setBounds(0, 20 * (i++), 120, 20);
    addAndMakeVisible(MixKnobLabel);
    
    MixKnob.setSliderStyle(juce::Slider::SliderStyle::ThreeValueHorizontal);
    MixKnob.setTextBoxStyle(juce::Slider::TextBoxRight, true, 40, 20);
    addAndMakeVisible(MixKnob);
    MixKnobAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(mProcessor.apvts, "SATURATOR_MIX", MixKnob);
    MixKnob.addListener(this);
    MixKnob.setMinAndMaxValues(mProcessor.knobValueMap["SATURATOR_MIX"].start, mProcessor.knobValueMap["SATURATOR_MIX"].end);
    MixKnob.setBounds(0, 20 * (i++), 120, 20);

    VolumeKnobLabel.setText("Post Gain", juce::NotificationType::dontSendNotification);
    VolumeKnobLabel.setBounds(0, 20 * (i++), 120, 20);
    addAndMakeVisible(VolumeKnobLabel);

    VolumeKnob.setSliderStyle(juce::Slider::SliderStyle::ThreeValueHorizontal);
    VolumeKnob.setTextBoxStyle(juce::Slider::TextBoxRight, true, 40, 20);
    addAndMakeVisible(VolumeKnob);
    VolumeKnobAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(mProcessor.apvts, "SATURATOR_POST_GAIN", VolumeKnob);
    VolumeKnob.addListener(this);
    VolumeKnob.setMinAndMaxValues(mProcessor.knobValueMap["SATURATOR_POST_GAIN"].start, mProcessor.knobValueMap["SATURATOR_POST_GAIN"].end);
    VolumeKnob.setBounds(0, 20 * (i++), 120, 20);
    
    
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

void SaturatorEditor::sliderValueChanged(juce::Slider* slider)
{
    if (slider == &GainKnob)
    {
        if (abs(GainKnob.getMinValue() - mProcessor.knobValueMap["SATURATOR_PRE_GAIN"].start) < 1e-3 || abs(GainKnob.getMaxValue() - mProcessor.knobValueMap["SATURATOR_PRE_GAIN"].end) < 1e-3)
            mProcessor.knobValueMap.set("SATURATOR_PRE_GAIN", juce::NormalisableRange<float>(GainKnob.getMinValue(), GainKnob.getMaxValue()));
    }
    else if (slider == &MixKnob)
    {
        if (abs(MixKnob.getMinValue() - mProcessor.knobValueMap["SATURATOR_MIX"].start) < 1e-3 || abs(MixKnob.getMaxValue() - mProcessor.knobValueMap["SATURATOR_MIX"].end) < 1e-3)
            mProcessor.knobValueMap.set("SATURATOR_MIX", juce::NormalisableRange<float>(MixKnob.getMinValue(), MixKnob.getMaxValue()));
    }
    else if (slider == &VolumeKnob)
    {
        if (abs(VolumeKnob.getMinValue() - mProcessor.knobValueMap["SATURATOR_POST_GAIN"].start) < 1e-3 || abs(VolumeKnob.getMaxValue() - mProcessor.knobValueMap["SATURATOR_POST_GAIN"].end) < 1e-3)
            mProcessor.knobValueMap.set("SATURATOR_POST_GAIN", juce::NormalisableRange<float>(VolumeKnob.getMinValue(), VolumeKnob.getMaxValue()));
    }
}

void SaturatorEditor::oneKnobMapping(float oneKnobSliderValue)
{
    GainKnob.setValue(mProcessor.knobValueMap["SATURATOR_PRE_GAIN"].convertFrom0to1(oneKnobSliderValue));
    MixKnob.setValue(mProcessor.knobValueMap["SATURATOR_MIX"].convertFrom0to1(oneKnobSliderValue));
    VolumeKnob.setValue(mProcessor.knobValueMap["SATURATOR_POST_GAIN"].convertFrom0to1(oneKnobSliderValue));
}