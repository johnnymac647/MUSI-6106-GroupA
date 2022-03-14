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
    int i = 1;

    InputGainKnobLabel.setText("Pre Gain", juce::NotificationType::dontSendNotification);
    InputGainKnobLabel.setBounds(0, 20 * (i++), 120, 20);
    addAndMakeVisible(InputGainKnobLabel);

    InputGainKnob.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    InputGainKnob.setTextBoxStyle(juce::Slider::TextBoxRight, true, 40, 20);
    addAndMakeVisible(InputGainKnob);
    InputGainKnobAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(mProcessor.apvts, "COMPRESSOR_PRE_GAIN", InputGainKnob);
    InputGainKnob.setBounds(0, 20 * (i++), 120, 20);

    ThresholdKnobLabel.setText("Threshold", juce::NotificationType::dontSendNotification);
    ThresholdKnobLabel.setBounds(0, 20 * (i++), 120, 20);
    addAndMakeVisible(ThresholdKnobLabel);
    
    ThresholdKnob.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    ThresholdKnob.setTextBoxStyle(juce::Slider::TextBoxRight, true, 40, 20);
    addAndMakeVisible(ThresholdKnob);
    ThresholdKnobAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(mProcessor.apvts, "COMPRESSOR_THRESHOLD", ThresholdKnob);
    ThresholdKnob.setBounds(0, 20 * (i++), 120, 20);

    RatioKnobLabel.setText("Ratio", juce::NotificationType::dontSendNotification);
    RatioKnobLabel.setBounds(0, 20 * (i++), 120, 20);
    addAndMakeVisible(RatioKnobLabel);

    RatioKnob.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    RatioKnob.setTextBoxStyle(juce::Slider::TextBoxRight, true, 40, 20);
    addAndMakeVisible(RatioKnob);
    RatioKnobAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(mProcessor.apvts, "COMPRESSOR_RATIO", RatioKnob);
    RatioKnob.setBounds(0, 20 * (i++), 120, 20);

    AttackKnobLabel.setText("Attack", juce::NotificationType::dontSendNotification);
    AttackKnobLabel.setBounds(0, 20 * (i++), 120, 20);
    addAndMakeVisible(AttackKnobLabel);

    AttackKnob.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    AttackKnob.setTextBoxStyle(juce::Slider::TextBoxRight, true, 40, 20);
    addAndMakeVisible(AttackKnob);
    AttackKnobAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(mProcessor.apvts, "COMPRESSOR_ATTACK", AttackKnob);
    AttackKnob.setBounds(0, 20 * (i++), 120, 20);

    ReleaseKnobLabel.setText("Release", juce::NotificationType::dontSendNotification);
    ReleaseKnobLabel.setBounds(0, 20 * (i++), 120, 20);
    addAndMakeVisible(ReleaseKnobLabel);

    ReleaseKnob.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    ReleaseKnob.setTextBoxStyle(juce::Slider::TextBoxRight, true, 40, 20);
    addAndMakeVisible(ReleaseKnob);
    ReleaseKnobAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(mProcessor.apvts, "COMPRESSOR_RELEASE", ReleaseKnob);
    ReleaseKnob.setBounds(0, 20 * (i++), 120, 20);

    MakeUpGainKnobLabel.setText("MakeUpGain", juce::NotificationType::dontSendNotification);
    MakeUpGainKnobLabel.setBounds(0, 20 * (i++), 120, 20);
    addAndMakeVisible(MakeUpGainKnobLabel);
    
    MakeUpGainKnob.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    MakeUpGainKnob.setTextBoxStyle(juce::Slider::TextBoxRight, true, 40, 20);
    addAndMakeVisible(MakeUpGainKnob);
    MakeUpGainKnobAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(mProcessor.apvts, "COMPRESSOR_MAKEUP_GAIN", MakeUpGainKnob);
    MakeUpGainKnob.setBounds(0, 20 * (i++), 120, 20);

    OutputGainKnobLabel.setText("OutputGain", juce::NotificationType::dontSendNotification);
    OutputGainKnobLabel.setBounds(0, 20 * (i++), 120, 20);
    addAndMakeVisible(OutputGainKnobLabel);
    
    OutputGainKnob.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    OutputGainKnob.setTextBoxStyle(juce::Slider::TextBoxRight, true, 40, 20);
    addAndMakeVisible(OutputGainKnob);
    OutputGainKnobAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(mProcessor.apvts, "COMPRESSOR_POST_GAIN", OutputGainKnob);
    OutputGainKnob.setBounds(0, 20 * (i++), 120, 20);
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
