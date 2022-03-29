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
    int i = 1;

    VolumeButton.setClickingTogglesState(true);
    VolumeButton.setBounds(90, 20 * i, 20, 20);
    VolumeButton.onClick = [this] { updateToggleState(&VolumeButton); };

    VolumeKnobLabel.setText("Post Gain", juce::NotificationType::dontSendNotification);
    VolumeKnobLabel.setBounds(0, 20 * (i++), 120, 20);
    addAndMakeVisible(VolumeKnobLabel);

    addAndMakeVisible(VolumeButton);

    VolumeKnob.setSliderStyle(juce::Slider::SliderStyle::ThreeValueHorizontal);
    VolumeKnob.setTextBoxStyle(juce::Slider::TextBoxRight, true, 40, 20);
    VolumeKnob.addListener(this);
    addAndMakeVisible(VolumeKnob);
    VolumeKnobAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(mProcessor.apvts, "GATE_POST_GAIN", VolumeKnob);
    VolumeKnob.setMinAndMaxValues(mProcessor.knobValueMap["GATE_POST_GAIN"].start, mProcessor.knobValueMap["GATE_POST_GAIN"].end);
    VolumeKnob.setBounds(0, 20 * (i++), 120, 20);

    ThresholdKnobLabel.setText("Threshold", juce::NotificationType::dontSendNotification);
    ThresholdKnobLabel.setBounds(0, 20 * (i++), 120, 20);
    addAndMakeVisible(ThresholdKnobLabel);

    ThresholdKnob.setSliderStyle(juce::Slider::SliderStyle::ThreeValueHorizontal);
    ThresholdKnob.setTextBoxStyle(juce::Slider::TextBoxRight, true, 40, 20);
    ThresholdKnob.addListener(this);
    addAndMakeVisible(ThresholdKnob);
    ThresholdKnobAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(mProcessor.apvts, "GATE_THRESHOLD", ThresholdKnob);
    ThresholdKnob.setMinAndMaxValues(mProcessor.knobValueMap["GATE_THRESHOLD"].start, mProcessor.knobValueMap["GATE_THRESHOLD"].end);
    ThresholdKnob.setBounds(0, 20 * (i++), 120, 20);

    RatioKnobLabel.setText("Ratio", juce::NotificationType::dontSendNotification);
    RatioKnobLabel.setBounds(0, 20 * (i++), 120, 20);
    addAndMakeVisible(RatioKnobLabel);

    RatioKnob.setSliderStyle(juce::Slider::SliderStyle::ThreeValueHorizontal);
    RatioKnob.setTextBoxStyle(juce::Slider::TextBoxRight, true, 40, 20);
    RatioKnob.addListener(this);
    addAndMakeVisible(RatioKnob);
    RatioKnobAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(mProcessor.apvts, "GATE_RATIO", RatioKnob);
    RatioKnob.setMinAndMaxValues(mProcessor.knobValueMap["GATE_RATIO"].start, mProcessor.knobValueMap["GATE_RATIO"].end);
    RatioKnob.setBounds(0, 20 * (i++), 120, 20);

    AttackKnobLabel.setText("Attack", juce::NotificationType::dontSendNotification);
    AttackKnobLabel.setBounds(0, 20 * (i++), 120, 20);
    addAndMakeVisible(AttackKnobLabel);

    AttackKnob.setSliderStyle(juce::Slider::SliderStyle::ThreeValueHorizontal);
    AttackKnob.setTextBoxStyle(juce::Slider::TextBoxRight, true, 40, 20);
    AttackKnob.addListener(this);
    addAndMakeVisible(AttackKnob);
    AttackKnobAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(mProcessor.apvts, "GATE_ATTACK", AttackKnob);
    AttackKnob.setMinAndMaxValues(mProcessor.knobValueMap["GATE_ATTACK"].start, mProcessor.knobValueMap["GATE_ATTACK"].end);
    AttackKnob.setBounds(0, 20 * (i++), 120, 20);

    ReleaseKnobLabel.setText("Release", juce::NotificationType::dontSendNotification);
    ReleaseKnobLabel.setBounds(0, 20 * (i++), 120, 20);
    addAndMakeVisible(ReleaseKnobLabel);

    ReleaseKnob.setSliderStyle(juce::Slider::SliderStyle::ThreeValueHorizontal);
    ReleaseKnob.setTextBoxStyle(juce::Slider::TextBoxRight, true, 40, 20);
    ReleaseKnob.addListener(this);
    addAndMakeVisible(ReleaseKnob);
    ReleaseKnobAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(mProcessor.apvts, "GATE_RELEASE", ReleaseKnob);
    ReleaseKnob.setMinAndMaxValues(mProcessor.knobValueMap["GATE_RELEASE"].start, mProcessor.knobValueMap["GATE_RELEASE"].end);
    ReleaseKnob.setBounds(0, 20 * (i++), 120, 20);

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

void GateEditor::sliderValueChanged(juce::Slider* slider)
{
    if (slider == &VolumeKnob)
    {
        if (abs(VolumeKnob.getMinValue() - mProcessor.knobValueMap["GATE_POST_GAIN"].start) < 1e-3 || abs(VolumeKnob.getMaxValue() - mProcessor.knobValueMap["GATE_POST_GAIN"].end) < 1e-3)
            mProcessor.knobValueMap.set("GATE_POST_GAIN", ModdedNormalisableRange<float>(VolumeKnob.getMinValue(), VolumeKnob.getMaxValue()));
    }
    else if (slider == &ThresholdKnob)
    {
        if (abs(ThresholdKnob.getMinValue() - mProcessor.knobValueMap["GATE_THRESHOLD"].start) < 1e-3 || abs(ThresholdKnob.getMaxValue() - mProcessor.knobValueMap["GATE_THRESHOLD"].end) < 1e-3)
            mProcessor.knobValueMap.set("GATE_THRESHOLD", ModdedNormalisableRange<float>(ThresholdKnob.getMinValue(), ThresholdKnob.getMaxValue()));
    }
    else if (slider == &RatioKnob)
    {
        if (abs(RatioKnob.getMinValue() - mProcessor.knobValueMap["GATE_RATIO"].start) < 1e-3 || abs(RatioKnob.getMaxValue() - mProcessor.knobValueMap["GATE_RATIO"].end) < 1e-3)
            mProcessor.knobValueMap.set("GATE_RATIO", ModdedNormalisableRange<float>(RatioKnob.getMinValue(), RatioKnob.getMaxValue()));
    }
    else if (slider == &AttackKnob)
    {
        if (abs(AttackKnob.getMinValue() - mProcessor.knobValueMap["GATE_ATTACK"].start) < 1e-3 || abs(AttackKnob.getMaxValue() - mProcessor.knobValueMap["GATE_ATTACK"].end) < 1e-3)
            mProcessor.knobValueMap.set("GATE_ATTACK", ModdedNormalisableRange<float>(AttackKnob.getMinValue(), AttackKnob.getMaxValue()));
    }
    else if (slider == &ReleaseKnob)
    {
        if (abs(ReleaseKnob.getMinValue() - mProcessor.knobValueMap["GATE_RELEASE"].start) < 1e-3 || abs(ReleaseKnob.getMaxValue() - mProcessor.knobValueMap["GATE_RELEASE"].end) < 1e-3)
            mProcessor.knobValueMap.set("GATE_RELEASE", ModdedNormalisableRange<float>(ReleaseKnob.getMinValue(), ReleaseKnob.getMaxValue()));
    }
}

void GateEditor::updateRanges()
{
    VolumeKnob.setMinAndMaxValues(mProcessor.knobValueMap["GATE_POST_GAIN"].start, mProcessor.knobValueMap["GATE_POST_GAIN"].end);
    ThresholdKnob.setMinAndMaxValues(mProcessor.knobValueMap["GATE_THRESHOLD"].start, mProcessor.knobValueMap["GATE_THRESHOLD"].end);
    RatioKnob.setMinAndMaxValues(mProcessor.knobValueMap["GATE_RATIO"].start, mProcessor.knobValueMap["GATE_RATIO"].end);
    AttackKnob.setMinAndMaxValues(mProcessor.knobValueMap["GATE_ATTACK"].start, mProcessor.knobValueMap["GATE_ATTACK"].end);
    ReleaseKnob.setMinAndMaxValues(mProcessor.knobValueMap["GATE_RELEASE"].start, mProcessor.knobValueMap["GATE_RELEASE"].end);
}