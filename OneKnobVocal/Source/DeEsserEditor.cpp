/*
  ==============================================================================

    DeEsserEditor.cpp
    Created: 6 Feb 2022 4:50:53pm
    Author:  yinsile

  ==============================================================================
*/

#include "DeEsserEditor.h"

DeEsserEditor::DeEsserEditor(OneKnobVocalAudioProcessor& p)
    :AudioProcessorEditor(&p), mProcessor(p)
{
    int i = 1;

    VolumeKnobLabel.setText("Post Gain", juce::NotificationType::dontSendNotification);
    VolumeKnobLabel.setBounds(0, 20 * (i++), 120, 20);
    addAndMakeVisible(VolumeKnobLabel);

    VolumeKnob.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    VolumeKnob.setTextBoxStyle(juce::Slider::TextBoxRight, true, 40, 20);
    addAndMakeVisible(VolumeKnob);
    VolumeKnobAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(mProcessor.apvts, "DEESSER_POST_GAIN", VolumeKnob);
    VolumeKnob.setBounds(0, 20 * (i++), 120, 20);

    ThresholdKnobLabel.setText("Threshold", juce::NotificationType::dontSendNotification);
    ThresholdKnobLabel.setBounds(0, 20 * (i++), 120, 20);
    addAndMakeVisible(ThresholdKnobLabel);

    ThresholdKnob.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    ThresholdKnob.setTextBoxStyle(juce::Slider::TextBoxRight, true, 40, 20);
    addAndMakeVisible(ThresholdKnob);
    ThresholdKnobAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(mProcessor.apvts, "DEESSER_THRESHOLD", ThresholdKnob);
    ThresholdKnob.setBounds(0, 20 * (i++), 120, 20);

    RatioKnobLabel.setText("Ratio", juce::NotificationType::dontSendNotification);
    RatioKnobLabel.setBounds(0, 20 * (i++), 120, 20);
    addAndMakeVisible(RatioKnobLabel);

    RatioKnob.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    RatioKnob.setTextBoxStyle(juce::Slider::TextBoxRight, true, 40, 20);
    addAndMakeVisible(RatioKnob);
    RatioKnobAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(mProcessor.apvts, "DEESSER_RATIO", RatioKnob);
    RatioKnob.setBounds(0, 20 * (i++), 120, 20);

    AttackKnobLabel.setText("Attack", juce::NotificationType::dontSendNotification);
    AttackKnobLabel.setBounds(0, 20 * (i++), 120, 20);
    addAndMakeVisible(AttackKnobLabel);

    AttackKnob.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    AttackKnob.setTextBoxStyle(juce::Slider::TextBoxRight, true, 40, 20);
    addAndMakeVisible(AttackKnob);
    AttackKnobAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(mProcessor.apvts, "DEESSER_ATTACK", AttackKnob);
    AttackKnob.setBounds(0, 20 * (i++), 120, 20);

    ReleaseKnobLabel.setText("Release", juce::NotificationType::dontSendNotification);
    ReleaseKnobLabel.setBounds(0, 20 * (i++), 120, 20);
    addAndMakeVisible(ReleaseKnobLabel);

    ReleaseKnob.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    ReleaseKnob.setTextBoxStyle(juce::Slider::TextBoxRight, true, 40, 20);
    addAndMakeVisible(ReleaseKnob);
    ReleaseKnobAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(mProcessor.apvts, "DEESSER_RELEASE", ReleaseKnob);
    ReleaseKnob.setBounds(0, 20 * (i++), 120, 20);

    CrossoverFreqKnobLabel.setText("Crossover Frequency", juce::NotificationType::dontSendNotification);
    CrossoverFreqKnobLabel.setBounds(0, 20 * (i++), 120, 20);
    addAndMakeVisible(CrossoverFreqKnobLabel);

    CrossoverFreqKnob.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    CrossoverFreqKnob.setTextBoxStyle(juce::Slider::TextBoxRight, true, 40, 20);
    addAndMakeVisible(CrossoverFreqKnob);
    CrossoverFreqKnobAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(mProcessor.apvts, "DEESSER_CROSSOVERFREQ", CrossoverFreqKnob);
    CrossoverFreqKnob.setBounds(0, 20 * (i++), 120, 20);

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