/*
  ==============================================================================

    GateEditor.cpp
    Created: 6 Feb 2022 4:51:17pm
    Author:  yinsile

  ==============================================================================
*/

#include "GateEditor.h"

GateEditor::GateEditor(OneKnobVocalAudioProcessor& p)
    :AudioProcessorEditor(&p), mProcessor(p)
{
    VolumeKnob.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    VolumeKnob.setTextBoxStyle(juce::Slider::TextBoxRight, true, 40, 20);
    addAndMakeVisible(VolumeKnob);
    VolumeKnobAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(mProcessor.apvts, "GATE_POST_GAIN", VolumeKnob);
    VolumeKnob.setBounds(0, 40, 120, 20);

    ThresholdKnob.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    ThresholdKnob.setTextBoxStyle(juce::Slider::TextBoxRight, true, 40, 20);
    addAndMakeVisible(ThresholdKnob);
    ThresholdKnobAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(mProcessor.apvts, "GATE_THRESHOLD", ThresholdKnob);
    ThresholdKnob.setBounds(0, 65, 120, 20);

    RatioKnob.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    RatioKnob.setTextBoxStyle(juce::Slider::TextBoxRight, true, 40, 20);
    addAndMakeVisible(RatioKnob);
    RatioKnobAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(mProcessor.apvts, "GATE_RATIO", RatioKnob);
    RatioKnob.setBounds(0, 90, 120, 20);

    AttackKnob.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    AttackKnob.setTextBoxStyle(juce::Slider::TextBoxRight, true, 40, 20);
    addAndMakeVisible(AttackKnob);
    AttackKnobAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(mProcessor.apvts, "GATE_ATTACK", AttackKnob);
    AttackKnob.setBounds(0, 115, 120, 20);

    ReleaseKnob.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    ReleaseKnob.setTextBoxStyle(juce::Slider::TextBoxRight, true, 40, 20);
    addAndMakeVisible(ReleaseKnob);
    ReleaseKnobAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(mProcessor.apvts, "GATE_RELEASE", ReleaseKnob);
    ReleaseKnob.setBounds(0, 140, 120, 20);

}

GateEditor::~GateEditor()
{

}

void GateEditor::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::crimson);

    g.setColour(juce::Colours::white);
    g.setFont(15.0f);
    g.drawFittedText("Gate", getLocalBounds(), juce::Justification::centredTop, 1);
}