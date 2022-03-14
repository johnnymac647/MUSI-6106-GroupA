/*
  ==============================================================================

    CompressorEditor.cpp
    Created: 6 Feb 2022 4:50:44pm
    Author:  yinsile

  ==============================================================================
*/

#include "CompressorEditor.h"

CompressorEditor::CompressorEditor(OneKnobVocalAudioProcessor& p)
    :AudioProcessorEditor(&p), mProcessor(p)
{
    InputGainKnob.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    InputGainKnob.setTextBoxStyle(juce::Slider::TextBoxRight, true, 40, 20);
    addAndMakeVisible(InputGainKnob);
    InputGainKnobAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(mProcessor.apvts, "COMPRESSOR_PRE_GAIN", InputGainKnob);
    InputGainKnob.setBounds(0, 40, 120, 20);
    
    ThresholdKnob.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    ThresholdKnob.setTextBoxStyle(juce::Slider::TextBoxRight, true, 40, 20);
    addAndMakeVisible(ThresholdKnob);
    ThresholdKnobAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(mProcessor.apvts, "COMPRESSOR_THRESHOLD", ThresholdKnob);
    ThresholdKnob.setBounds(0, 65, 120, 20);

    RatioKnob.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    RatioKnob.setTextBoxStyle(juce::Slider::TextBoxRight, true, 40, 20);
    addAndMakeVisible(RatioKnob);
    RatioKnobAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(mProcessor.apvts, "COMPRESSOR_RATIO", RatioKnob);
    RatioKnob.setBounds(0, 90, 120, 20);

    AttackKnob.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    AttackKnob.setTextBoxStyle(juce::Slider::TextBoxRight, true, 40, 20);
    addAndMakeVisible(AttackKnob);
    AttackKnobAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(mProcessor.apvts, "COMPRESSOR_ATTACK", AttackKnob);
    AttackKnob.setBounds(0, 115, 120, 20);

    ReleaseKnob.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    ReleaseKnob.setTextBoxStyle(juce::Slider::TextBoxRight, true, 40, 20);
    addAndMakeVisible(ReleaseKnob);
    ReleaseKnobAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(mProcessor.apvts, "COMPRESSOR_RELEASE", ReleaseKnob);
    ReleaseKnob.setBounds(0, 140, 120, 20);
    
    MakeUpGainKnob.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    MakeUpGainKnob.setTextBoxStyle(juce::Slider::TextBoxRight, true, 40, 20);
    addAndMakeVisible(MakeUpGainKnob);
    MakeUpGainKnobAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(mProcessor.apvts, "COMPRESSOR_MAKEUP_GAIN", MakeUpGainKnob);
    MakeUpGainKnob.setBounds(0, 165, 120, 20);
    
    OutputGainKnob.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    OutputGainKnob.setTextBoxStyle(juce::Slider::TextBoxRight, true, 40, 20);
    addAndMakeVisible(OutputGainKnob);
    OutputGainKnobAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(mProcessor.apvts, "COMPRESSOR_POST_GAIN", OutputGainKnob);
    OutputGainKnob.setBounds(0, 190, 120, 20);
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
