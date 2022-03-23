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

    InputGainKnob.setSliderStyle(juce::Slider::SliderStyle::ThreeValueHorizontal);
    InputGainKnob.setTextBoxStyle(juce::Slider::TextBoxRight, true, 40, 20);
    addAndMakeVisible(InputGainKnob);
    InputGainKnobAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(mProcessor.apvts, "COMPRESSOR_PRE_GAIN", InputGainKnob);
    InputGainKnob.addListener(this);
    InputGainKnob.setMinAndMaxValues(mProcessor.knobValueMap["COMPRESSOR_PRE_GAIN"].start, mProcessor.knobValueMap["COMPRESSOR_PRE_GAIN"].end);
    InputGainKnob.setBounds(0, 20 * (i++), 120, 20);

    ThresholdKnobLabel.setText("Threshold", juce::NotificationType::dontSendNotification);
    ThresholdKnobLabel.setBounds(0, 20 * (i++), 120, 20);
    addAndMakeVisible(ThresholdKnobLabel);
    
    ThresholdKnob.setSliderStyle(juce::Slider::SliderStyle::ThreeValueHorizontal);
    ThresholdKnob.setTextBoxStyle(juce::Slider::TextBoxRight, true, 40, 20);
    addAndMakeVisible(ThresholdKnob);
    ThresholdKnobAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(mProcessor.apvts, "COMPRESSOR_THRESHOLD", ThresholdKnob);
    ThresholdKnob.addListener(this);
    ThresholdKnob.setMinAndMaxValues(mProcessor.knobValueMap["COMPRESSOR_THRESHOLD"].start, mProcessor.knobValueMap["COMPRESSOR_THRESHOLD"].end);
    ThresholdKnob.setBounds(0, 20 * (i++), 120, 20);

    RatioKnobLabel.setText("Ratio", juce::NotificationType::dontSendNotification);
    RatioKnobLabel.setBounds(0, 20 * (i++), 120, 20);
    addAndMakeVisible(RatioKnobLabel);

    RatioKnob.setSliderStyle(juce::Slider::SliderStyle::ThreeValueHorizontal);
    RatioKnob.setTextBoxStyle(juce::Slider::TextBoxRight, true, 40, 20);
    addAndMakeVisible(RatioKnob);
    RatioKnobAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(mProcessor.apvts, "COMPRESSOR_RATIO", RatioKnob);
    RatioKnob.addListener(this);
    RatioKnob.setMinAndMaxValues(mProcessor.knobValueMap["COMPRESSOR_RATIO"].start, mProcessor.knobValueMap["COMPRESSOR_RATIO"].end);
    RatioKnob.setBounds(0, 20 * (i++), 120, 20);

    AttackKnobLabel.setText("Attack", juce::NotificationType::dontSendNotification);
    AttackKnobLabel.setBounds(0, 20 * (i++), 120, 20);
    addAndMakeVisible(AttackKnobLabel);

    AttackKnob.setSliderStyle(juce::Slider::SliderStyle::ThreeValueHorizontal);
    AttackKnob.setTextBoxStyle(juce::Slider::TextBoxRight, true, 40, 20);
    addAndMakeVisible(AttackKnob);
    AttackKnobAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(mProcessor.apvts, "COMPRESSOR_ATTACK", AttackKnob);
    AttackKnob.addListener(this);
    AttackKnob.setMinAndMaxValues(mProcessor.knobValueMap["COMPRESSOR_ATTACK"].start, mProcessor.knobValueMap["COMPRESSOR_ATTACK"].end);
    AttackKnob.setBounds(0, 20 * (i++), 120, 20);

    ReleaseKnobLabel.setText("Release", juce::NotificationType::dontSendNotification);
    ReleaseKnobLabel.setBounds(0, 20 * (i++), 120, 20);
    addAndMakeVisible(ReleaseKnobLabel);

    ReleaseKnob.setSliderStyle(juce::Slider::SliderStyle::ThreeValueHorizontal);
    ReleaseKnob.setTextBoxStyle(juce::Slider::TextBoxRight, true, 40, 20);
    addAndMakeVisible(ReleaseKnob);
    ReleaseKnobAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(mProcessor.apvts, "COMPRESSOR_RELEASE", ReleaseKnob);
    ReleaseKnob.addListener(this);
    ReleaseKnob.setMinAndMaxValues(mProcessor.knobValueMap["COMPRESSOR_RELEASE"].start, mProcessor.knobValueMap["COMPRESSOR_RELEASE"].end);
    ReleaseKnob.setBounds(0, 20 * (i++), 120, 20);

    MakeUpGainKnobLabel.setText("MakeUpGain", juce::NotificationType::dontSendNotification);
    MakeUpGainKnobLabel.setBounds(0, 20 * (i++), 120, 20);
    addAndMakeVisible(MakeUpGainKnobLabel);
    
    MakeUpGainKnob.setSliderStyle(juce::Slider::SliderStyle::ThreeValueHorizontal);
    MakeUpGainKnob.setTextBoxStyle(juce::Slider::TextBoxRight, true, 40, 20);
    addAndMakeVisible(MakeUpGainKnob);
    MakeUpGainKnobAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(mProcessor.apvts, "COMPRESSOR_MAKEUP_GAIN", MakeUpGainKnob);
    MakeUpGainKnob.addListener(this);
    MakeUpGainKnob.setMinAndMaxValues(mProcessor.knobValueMap["COMPRESSOR_MAKEUP_GAIN"].start, mProcessor.knobValueMap["COMPRESSOR_MAKEUP_GAIN"].end);
    MakeUpGainKnob.setBounds(0, 20 * (i++), 120, 20);

    OutputGainKnobLabel.setText("OutputGain", juce::NotificationType::dontSendNotification);
    OutputGainKnobLabel.setBounds(0, 20 * (i++), 120, 20);
    addAndMakeVisible(OutputGainKnobLabel);
    
    OutputGainKnob.setSliderStyle(juce::Slider::SliderStyle::ThreeValueHorizontal);
    OutputGainKnob.setTextBoxStyle(juce::Slider::TextBoxRight, true, 40, 20);
    addAndMakeVisible(OutputGainKnob);
    OutputGainKnobAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(mProcessor.apvts, "COMPRESSOR_POST_GAIN", OutputGainKnob);
    OutputGainKnob.addListener(this);
    OutputGainKnob.setMinAndMaxValues(mProcessor.knobValueMap["COMPRESSOR_POST_GAIN"].start, mProcessor.knobValueMap["COMPRESSOR_POST_GAIN"].end);
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

void CompressorEditor::sliderValueChanged(juce::Slider* slider)
{
    if (slider == &InputGainKnob)
    {
        if (abs(InputGainKnob.getMinValue() - mProcessor.knobValueMap["COMPRESSOR_PRE_GAIN"].start) < 1e-3 || abs(InputGainKnob.getMaxValue() - mProcessor.knobValueMap["COMPRESSOR_PRE_GAIN"].end) < 1e-3)
            mProcessor.knobValueMap.set("COMPRESSOR_PRE_GAIN", ModdedNormalisableRange<float>(InputGainKnob.getMinValue(), InputGainKnob.getMaxValue()));
    }
    else if (slider == &ThresholdKnob)
    {
        if (abs(ThresholdKnob.getMinValue() - mProcessor.knobValueMap["COMPRESSOR_THRESHOLD"].start) < 1e-3 || abs(ThresholdKnob.getMaxValue() - mProcessor.knobValueMap["COMPRESSOR_THRESHOLD"].end) < 1e-3)
            mProcessor.knobValueMap.set("COMPRESSOR_THRESHOLD", ModdedNormalisableRange<float>(ThresholdKnob.getMinValue(), ThresholdKnob.getMaxValue()));
    }
    else if (slider == &RatioKnob)
    {
        if (abs(RatioKnob.getMinValue() - mProcessor.knobValueMap["COMPRESSOR_RATIO"].start) < 1e-3 || abs(RatioKnob.getMaxValue() - mProcessor.knobValueMap["COMPRESSOR_RATIO"].end) < 1e-3)
            mProcessor.knobValueMap.set("COMPRESSOR_RATIO", ModdedNormalisableRange<float>(RatioKnob.getMinValue(), RatioKnob.getMaxValue()));
    }
    else if (slider == &AttackKnob)
    {
        if (abs(AttackKnob.getMinValue() - mProcessor.knobValueMap["COMPRESSOR_ATTACK"].start) < 1e-3 || abs(AttackKnob.getMaxValue() - mProcessor.knobValueMap["COMPRESSOR_ATTACK"].end) < 1e-3)
            mProcessor.knobValueMap.set("COMPRESSOR_ATTACK", ModdedNormalisableRange<float>(AttackKnob.getMinValue(), AttackKnob.getMaxValue()));
    }
    else if (slider == &ReleaseKnob)
    {
        if (abs(ReleaseKnob.getMinValue() - mProcessor.knobValueMap["COMPRESSOR_RELEASE"].start) < 1e-3 || abs(ReleaseKnob.getMaxValue() - mProcessor.knobValueMap["COMPRESSOR_RELEASE"].end) < 1e-3)
            mProcessor.knobValueMap.set("COMPRESSOR_RELEASE", ModdedNormalisableRange<float>(ReleaseKnob.getMinValue(), ReleaseKnob.getMaxValue()));
    }
    else if (slider == &MakeUpGainKnob)
    {
        if (abs(MakeUpGainKnob.getMinValue() - mProcessor.knobValueMap["COMPRESSOR_MAKEUP_GAIN"].start) < 1e-3 || abs(MakeUpGainKnob.getMaxValue() - mProcessor.knobValueMap["COMPRESSOR_MAKEUP_GAIN"].end) < 1e-3)
            mProcessor.knobValueMap.set("COMPRESSOR_MAKEUP_GAIN", ModdedNormalisableRange<float>(MakeUpGainKnob.getMinValue(), MakeUpGainKnob.getMaxValue()));
    }
    else if (slider == &OutputGainKnob)
    {
        if (abs(OutputGainKnob.getMinValue() - mProcessor.knobValueMap["COMPRESSOR_POST_GAIN"].start) < 1e-3 || abs(OutputGainKnob.getMaxValue() - mProcessor.knobValueMap["COMPRESSOR_POST_GAIN"].end) < 1e-3)
            mProcessor.knobValueMap.set("COMPRESSOR_POST_GAIN", ModdedNormalisableRange<float>(OutputGainKnob.getMinValue(), OutputGainKnob.getMaxValue()));
    }
}

void CompressorEditor::updateRanges()
{
    InputGainKnob.setMinAndMaxValues(mProcessor.knobValueMap["COMPRESSOR_PRE_GAIN"].start, mProcessor.knobValueMap["COMPRESSOR_PRE_GAIN"].end);
    ThresholdKnob.setMinAndMaxValues(mProcessor.knobValueMap["COMPRESSOR_THRESHOLD"].start, mProcessor.knobValueMap["COMPRESSOR_THRESHOLD"].end);
    RatioKnob.setMinAndMaxValues(mProcessor.knobValueMap["COMPRESSOR_RATIO"].start, mProcessor.knobValueMap["COMPRESSOR_RATIO"].end);
    AttackKnob.setMinAndMaxValues(mProcessor.knobValueMap["COMPRESSOR_ATTACK"].start, mProcessor.knobValueMap["COMPRESSOR_ATTACK"].end);
    ReleaseKnob.setMinAndMaxValues(mProcessor.knobValueMap["COMPRESSOR_RELEASE"].start, mProcessor.knobValueMap["COMPRESSOR_RELEASE"].end);
    MakeUpGainKnob.setMinAndMaxValues(mProcessor.knobValueMap["COMPRESSOR_MAKEUP_GAIN"].start, mProcessor.knobValueMap["COMPRESSOR_MAKEUP_GAIN"].end);
    OutputGainKnob.setMinAndMaxValues(mProcessor.knobValueMap["COMPRESSOR_POST_GAIN"].start, mProcessor.knobValueMap["COMPRESSOR_POST_GAIN"].end);
}