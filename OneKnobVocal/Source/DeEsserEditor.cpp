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

    VolumeKnob.setSliderStyle(juce::Slider::SliderStyle::ThreeValueHorizontal);
    VolumeKnob.setTextBoxStyle(juce::Slider::TextBoxRight, true, 40, 20);
    addAndMakeVisible(VolumeKnob);
    VolumeKnobAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(mProcessor.apvts, "DEESSER_POST_GAIN", VolumeKnob);
    VolumeKnob.addListener(this);
    VolumeKnob.setMinAndMaxValues(mProcessor.knobValueMap["DEESSER_POST_GAIN"].start, mProcessor.knobValueMap["DEESSER_POST_GAIN"].end);
    VolumeKnob.setBounds(0, 20 * (i++), 120, 20);

    ThresholdKnobLabel.setText("Threshold", juce::NotificationType::dontSendNotification);
    ThresholdKnobLabel.setBounds(0, 20 * (i++), 120, 20);
    addAndMakeVisible(ThresholdKnobLabel);

    ThresholdKnob.setSliderStyle(juce::Slider::SliderStyle::ThreeValueHorizontal);
    ThresholdKnob.setTextBoxStyle(juce::Slider::TextBoxRight, true, 40, 20);
    addAndMakeVisible(ThresholdKnob);
    ThresholdKnobAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(mProcessor.apvts, "DEESSER_THRESHOLD", ThresholdKnob);
    ThresholdKnob.addListener(this);
    ThresholdKnob.setMinAndMaxValues(mProcessor.knobValueMap["DEESSER_THRESHOLD"].start, mProcessor.knobValueMap["DEESSER_THRESHOLD"].end);
    ThresholdKnob.setBounds(0, 20 * (i++), 120, 20);

    RatioKnobLabel.setText("Ratio", juce::NotificationType::dontSendNotification);
    RatioKnobLabel.setBounds(0, 20 * (i++), 120, 20);
    addAndMakeVisible(RatioKnobLabel);

    RatioKnob.setSliderStyle(juce::Slider::SliderStyle::ThreeValueHorizontal);
    RatioKnob.setTextBoxStyle(juce::Slider::TextBoxRight, true, 40, 20);
    addAndMakeVisible(RatioKnob);
    RatioKnobAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(mProcessor.apvts, "DEESSER_RATIO", RatioKnob);
    RatioKnob.addListener(this);
    RatioKnob.setMinAndMaxValues(mProcessor.knobValueMap["DEESSER_RATIO"].start, mProcessor.knobValueMap["DEESSER_RATIO"].end);
    RatioKnob.setBounds(0, 20 * (i++), 120, 20);

    AttackKnobLabel.setText("Attack", juce::NotificationType::dontSendNotification);
    AttackKnobLabel.setBounds(0, 20 * (i++), 120, 20);
    addAndMakeVisible(AttackKnobLabel);

    AttackKnob.setSliderStyle(juce::Slider::SliderStyle::ThreeValueHorizontal);
    AttackKnob.setTextBoxStyle(juce::Slider::TextBoxRight, true, 40, 20);
    addAndMakeVisible(AttackKnob);
    AttackKnobAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(mProcessor.apvts, "DEESSER_ATTACK", AttackKnob);
    AttackKnob.addListener(this);
    AttackKnob.setMinAndMaxValues(mProcessor.knobValueMap["DEESSER_ATTACK"].start, mProcessor.knobValueMap["DEESSER_ATTACK"].end);
    AttackKnob.setBounds(0, 20 * (i++), 120, 20);

    ReleaseKnobLabel.setText("Release", juce::NotificationType::dontSendNotification);
    ReleaseKnobLabel.setBounds(0, 20 * (i++), 120, 20);
    addAndMakeVisible(ReleaseKnobLabel);

    ReleaseKnob.setSliderStyle(juce::Slider::SliderStyle::ThreeValueHorizontal);
    ReleaseKnob.setTextBoxStyle(juce::Slider::TextBoxRight, true, 40, 20);
    addAndMakeVisible(ReleaseKnob);
    ReleaseKnobAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(mProcessor.apvts, "DEESSER_RELEASE", ReleaseKnob);
    ReleaseKnob.addListener(this);
    ReleaseKnob.setMinAndMaxValues(mProcessor.knobValueMap["DEESSER_RELEASE"].start, mProcessor.knobValueMap["DEESSER_RELEASE"].end);
    ReleaseKnob.setBounds(0, 20 * (i++), 120, 20);

    CrossoverFreqKnobLabel.setText("Crossover Frequency", juce::NotificationType::dontSendNotification);
    CrossoverFreqKnobLabel.setBounds(0, 20 * (i++), 120, 20);
    addAndMakeVisible(CrossoverFreqKnobLabel);

    CrossoverFreqKnob.setSliderStyle(juce::Slider::SliderStyle::ThreeValueHorizontal);
    CrossoverFreqKnob.setTextBoxStyle(juce::Slider::TextBoxRight, true, 40, 20);
    addAndMakeVisible(CrossoverFreqKnob);
    CrossoverFreqKnobAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(mProcessor.apvts, "DEESSER_CROSSOVERFREQ", CrossoverFreqKnob);
    CrossoverFreqKnob.addListener(this);
    CrossoverFreqKnob.setMinAndMaxValues(mProcessor.knobValueMap["DEESSER_CROSSOVERFREQ"].start, mProcessor.knobValueMap["DEESSER_CROSSOVERFREQ"].end);
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

void DeEsserEditor::sliderValueChanged(juce::Slider* slider)
{
    if (slider == &VolumeKnob)
    {
        if (abs(VolumeKnob.getMinValue() - mProcessor.knobValueMap["DEESSER_POST_GAIN"].start) < 1e-3 || abs(VolumeKnob.getMaxValue() - mProcessor.knobValueMap["DEESSER_POST_GAIN"].end) < 1e-3)
            mProcessor.knobValueMap.set("DEESSER_POST_GAIN", ModdedNormalisableRange<float>(VolumeKnob.getMinValue(), VolumeKnob.getMaxValue()));
    }
    else if (slider == &ThresholdKnob)
    {
        if (abs(ThresholdKnob.getMinValue() - mProcessor.knobValueMap["DEESSER_THRESHOLD"].start) < 1e-3 || abs(ThresholdKnob.getMaxValue() - mProcessor.knobValueMap["DEESSER_THRESHOLD"].end) < 1e-3)
            mProcessor.knobValueMap.set("DEESSER_THRESHOLD", ModdedNormalisableRange<float>(ThresholdKnob.getMinValue(), ThresholdKnob.getMaxValue()));
    }
    else if (slider == &RatioKnob)
    {
        if (abs(RatioKnob.getMinValue() - mProcessor.knobValueMap["DEESSER_RATIO"].start) < 1e-3 || abs(RatioKnob.getMaxValue() - mProcessor.knobValueMap["DEESSER_RATIO"].end) < 1e-3)
            mProcessor.knobValueMap.set("DEESSER_RATIO", ModdedNormalisableRange<float>(RatioKnob.getMinValue(), RatioKnob.getMaxValue()));
    }
    else if (slider == &AttackKnob)
    {
        if (abs(AttackKnob.getMinValue() - mProcessor.knobValueMap["DEESSER_ATTACK"].start) < 1e-3 || abs(AttackKnob.getMaxValue() - mProcessor.knobValueMap["DEESSER_ATTACK"].end) < 1e-3)
            mProcessor.knobValueMap.set("DEESSER_ATTACK", ModdedNormalisableRange<float>(AttackKnob.getMinValue(), AttackKnob.getMaxValue()));
    }
    else if (slider == &ReleaseKnob)
    {
        if (abs(ReleaseKnob.getMinValue() - mProcessor.knobValueMap["DEESSER_RELEASE"].start) < 1e-3 || abs(ReleaseKnob.getMaxValue() - mProcessor.knobValueMap["DEESSER_RELEASE"].end) < 1e-3)
            mProcessor.knobValueMap.set("DEESSER_RELEASE", ModdedNormalisableRange<float>(ReleaseKnob.getMinValue(), ReleaseKnob.getMaxValue()));
    }
    else if (slider == &CrossoverFreqKnob)
    {
        if (abs(CrossoverFreqKnob.getMinValue() - mProcessor.knobValueMap["DEESSER_CROSSOVERFREQ"].start) < 1e-3 || abs(CrossoverFreqKnob.getMaxValue() - mProcessor.knobValueMap["DEESSER_CROSSOVERFREQ"].end) < 1e-3)
            mProcessor.knobValueMap.set("DEESSER_CROSSOVERFREQ", ModdedNormalisableRange<float>(CrossoverFreqKnob.getMinValue(), CrossoverFreqKnob.getMaxValue()));
    }
}

void DeEsserEditor::updateRanges()
{
    VolumeKnob.setMinAndMaxValues(mProcessor.knobValueMap["DEESSER_POST_GAIN"].start, mProcessor.knobValueMap["DEESSER_POST_GAIN"].end);
    ThresholdKnob.setMinAndMaxValues(mProcessor.knobValueMap["DEESSER_THRESHOLD"].start, mProcessor.knobValueMap["DEESSER_THRESHOLD"].end);
    RatioKnob.setMinAndMaxValues(mProcessor.knobValueMap["DEESSER_RATIO"].start, mProcessor.knobValueMap["DEESSER_RATIO"].end);
    AttackKnob.setMinAndMaxValues(mProcessor.knobValueMap["DEESSER_ATTACK"].start, mProcessor.knobValueMap["DEESSER_ATTACK"].end);
    ReleaseKnob.setMinAndMaxValues(mProcessor.knobValueMap["DEESSER_RELEASE"].start, mProcessor.knobValueMap["DEESSER_RELEASE"].end);
    CrossoverFreqKnob.setMinAndMaxValues(mProcessor.knobValueMap["DEESSER_CROSSOVERFREQ"].start, mProcessor.knobValueMap["DEESSER_CROSSOVERFREQ"].end);
}