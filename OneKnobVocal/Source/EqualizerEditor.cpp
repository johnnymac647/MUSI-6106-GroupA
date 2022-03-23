/*
  ==============================================================================

    EqualizerEditor.cpp
    Created: 6 Feb 2022 4:51:05pm
    Author:  yinsile

  ==============================================================================
*/

#include "EqualizerEditor.h"

EqualizerEditor::EqualizerEditor(OneKnobVocalAudioProcessor& p)
    :AudioProcessorEditor(&p), mProcessor(p)
{
    int i = 1;

    PostGainLabel.setText("Post Gain", juce::NotificationType::dontSendNotification);
    PostGainLabel.setBounds(0, 20 * (i++), 120, 20);
    addAndMakeVisible(PostGainLabel);

    PostGainKnob.setSliderStyle(juce::Slider::SliderStyle::ThreeValueHorizontal);
    PostGainKnob.setTextBoxStyle(juce::Slider::TextBoxRight, true, 40, 20);
    PostGainKnobAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(mProcessor.apvts, "EQ_POST_GAIN", PostGainKnob);
    PostGainKnob.addListener(this);
    PostGainKnob.setMinAndMaxValues(mProcessor.knobValueMap["EQ_POST_GAIN"].start, mProcessor.knobValueMap["EQ_POST_GAIN"].end);
    PostGainKnob.setBounds(0, 20 * (i++), 120, 20);
    addAndMakeVisible(PostGainKnob);

    LowBandGainKnobLabel.setText("Low Band Gain", juce::NotificationType::dontSendNotification);
    LowBandGainKnobLabel.setBounds(0, 20 * (i++), 120, 20);
    addAndMakeVisible(LowBandGainKnobLabel);

    LowBandGainKnob.setSliderStyle(juce::Slider::SliderStyle::ThreeValueHorizontal);
    LowBandGainKnob.setTextBoxStyle(juce::Slider::TextBoxRight, true, 40, 20);
    LowBandGainKnobAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(mProcessor.apvts, "EQ_LOW_BAND_GAIN", LowBandGainKnob);
    LowBandGainKnob.addListener(this);
    LowBandGainKnob.setMinAndMaxValues(mProcessor.knobValueMap["EQ_LOW_BAND_GAIN"].start, mProcessor.knobValueMap["EQ_LOW_BAND_GAIN"].end);
    LowBandGainKnob.setBounds(0, 20 * (i++), 120, 20);
    addAndMakeVisible(LowBandGainKnob);

    LowBandCutoffKnobLabel.setText("Low Band Cutoff", juce::NotificationType::dontSendNotification);
    LowBandCutoffKnobLabel.setBounds(0, 20 * (i++), 120, 20);
    addAndMakeVisible(LowBandCutoffKnobLabel);

    LowBandCutoffKnob.setSliderStyle(juce::Slider::SliderStyle::ThreeValueHorizontal);
    LowBandCutoffKnob.setTextBoxStyle(juce::Slider::TextBoxRight, true, 40, 20);
    LowBandCutoffKnobAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(mProcessor.apvts, "EQ_LOW_BAND_CUTOFF", LowBandCutoffKnob);
    LowBandCutoffKnob.addListener(this);
    LowBandCutoffKnob.setMinAndMaxValues(mProcessor.knobValueMap["EQ_LOW_BAND_CUTOFF"].start, mProcessor.knobValueMap["EQ_LOW_BAND_CUTOFF"].end);
    LowBandCutoffKnob.setBounds(0, 20 * (i++), 120, 20);
    addAndMakeVisible(LowBandCutoffKnob);

    LowBandQualityKnobLabel.setText("Low Band Q", juce::NotificationType::dontSendNotification);
    LowBandQualityKnobLabel.setBounds(0, 20 * (i++), 120, 20);
    addAndMakeVisible(LowBandQualityKnobLabel);

    LowBandQualityKnob.setSliderStyle(juce::Slider::SliderStyle::ThreeValueHorizontal);
    LowBandQualityKnob.setTextBoxStyle(juce::Slider::TextBoxRight, true, 40, 20);
    LowBandQualityKnobAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(mProcessor.apvts, "EQ_LOW_BAND_QF", LowBandQualityKnob);
    LowBandQualityKnob.addListener(this);
    LowBandQualityKnob.setMinAndMaxValues(mProcessor.knobValueMap["EQ_LOW_BAND_QF"].start, mProcessor.knobValueMap["EQ_LOW_BAND_QF"].end);
    LowBandQualityKnob.setBounds(0, 20 * (i++), 120, 20);
    addAndMakeVisible(LowBandQualityKnob);

    LowMidBandGainKnobLabel.setText("Low-mid Band Gain", juce::NotificationType::dontSendNotification);
    LowMidBandGainKnobLabel.setBounds(0, 20 * (i++), 120, 20);
    addAndMakeVisible(LowMidBandGainKnobLabel);

    LowMidBandGainKnob.setSliderStyle(juce::Slider::SliderStyle::ThreeValueHorizontal);
    LowMidBandGainKnob.setTextBoxStyle(juce::Slider::TextBoxRight, true, 40, 20);
    LowMidBandGainKnobAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(mProcessor.apvts, "EQ_LOWMID_BAND_GAIN", LowMidBandGainKnob);
    LowMidBandGainKnob.addListener(this);
    LowMidBandGainKnob.setMinAndMaxValues(mProcessor.knobValueMap["EQ_LOWMID_BAND_GAIN"].start, mProcessor.knobValueMap["EQ_LOWMID_BAND_GAIN"].end);
    LowMidBandGainKnob.setBounds(0, 20 * (i++), 120, 20);
    addAndMakeVisible(LowMidBandGainKnob);

    LowMidBandFreqKnobLabel.setText("Low-mid Band Freq", juce::NotificationType::dontSendNotification);
    LowMidBandFreqKnobLabel.setBounds(0, 20 * (i++), 120, 20);
    addAndMakeVisible(LowMidBandFreqKnobLabel);

    LowMidBandFreqKnob.setSliderStyle(juce::Slider::SliderStyle::ThreeValueHorizontal);
    LowMidBandFreqKnob.setTextBoxStyle(juce::Slider::TextBoxRight, true, 40, 20);
    LowMidBandFreqKnobAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(mProcessor.apvts, "EQ_LOWMID_BAND_FREQ", LowMidBandFreqKnob);
    LowMidBandFreqKnob.addListener(this);
    LowMidBandFreqKnob.setMinAndMaxValues(mProcessor.knobValueMap["EQ_LOWMID_BAND_FREQ"].start, mProcessor.knobValueMap["EQ_LOWMID_BAND_FREQ"].end);
    LowMidBandFreqKnob.setBounds(0, 20 * (i++), 120, 20);
    addAndMakeVisible(LowMidBandFreqKnob);

    LowMidBandQualityKnobLabel.setText("Low-mid Band Q", juce::NotificationType::dontSendNotification);
    LowMidBandQualityKnobLabel.setBounds(0, 20 * (i++), 120, 20);
    addAndMakeVisible(LowMidBandQualityKnobLabel);

    LowMidBandQualityKnob.setSliderStyle(juce::Slider::SliderStyle::ThreeValueHorizontal);
    LowMidBandQualityKnob.setTextBoxStyle(juce::Slider::TextBoxRight, true, 40, 20);
    LowMidBandQualityKnobAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(mProcessor.apvts, "EQ_LOWMID_BAND_QF", LowMidBandQualityKnob);
    LowMidBandQualityKnob.addListener(this);
    LowMidBandQualityKnob.setMinAndMaxValues(mProcessor.knobValueMap["EQ_LOWMID_BAND_QF"].start, mProcessor.knobValueMap["EQ_LOWMID_BAND_QF"].end);
    LowMidBandQualityKnob.setBounds(0, 20 * (i++), 120, 20);
    addAndMakeVisible(LowMidBandQualityKnob);

    HighMidBandGainKnobLabel.setText("High-mid Band Gain", juce::NotificationType::dontSendNotification);
    HighMidBandGainKnobLabel.setBounds(0, 20 * (i++), 120, 20);
    addAndMakeVisible(HighMidBandGainKnobLabel);

    HighMidBandGainKnob.setSliderStyle(juce::Slider::SliderStyle::ThreeValueHorizontal);
    HighMidBandGainKnob.setTextBoxStyle(juce::Slider::TextBoxRight, true, 40, 20);
    HighMidBandGainKnobAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(mProcessor.apvts, "EQ_HIMID_BAND_GAIN", HighMidBandGainKnob);
    HighMidBandGainKnob.addListener(this);
    HighMidBandGainKnob.setMinAndMaxValues(mProcessor.knobValueMap["EQ_HIMID_BAND_GAIN"].start, mProcessor.knobValueMap["EQ_HIMID_BAND_GAIN"].end);
    HighMidBandGainKnob.setBounds(0, 20 * (i++), 120, 20);
    addAndMakeVisible(HighMidBandGainKnob);

    HighMidBandFreqKnobLabel.setText("High-mid Band Freq", juce::NotificationType::dontSendNotification);
    HighMidBandFreqKnobLabel.setBounds(0, 20 * (i++), 120, 20);
    addAndMakeVisible(HighMidBandFreqKnobLabel);

    HighMidBandFreqKnob.setSliderStyle(juce::Slider::SliderStyle::ThreeValueHorizontal);
    HighMidBandFreqKnob.setTextBoxStyle(juce::Slider::TextBoxRight, true, 40, 20);
    HighMidBandFreqKnobAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(mProcessor.apvts, "EQ_HIMID_BAND_FREQ", HighMidBandFreqKnob);
    HighMidBandFreqKnob.addListener(this);
    HighMidBandFreqKnob.setMinAndMaxValues(mProcessor.knobValueMap["EQ_HIMID_BAND_FREQ"].start, mProcessor.knobValueMap["EQ_HIMID_BAND_FREQ"].end);
    HighMidBandFreqKnob.setBounds(0, 20 * (i++), 120, 20);
    addAndMakeVisible(HighMidBandFreqKnob);

    HighMidBandQualityKnobLabel.setText("High-mid Band Q", juce::NotificationType::dontSendNotification);
    HighMidBandQualityKnobLabel.setBounds(0, 20 * (i++), 120, 20);
    addAndMakeVisible(HighMidBandQualityKnobLabel);

    HighMidBandQualityKnob.setSliderStyle(juce::Slider::SliderStyle::ThreeValueHorizontal);
    HighMidBandQualityKnob.setTextBoxStyle(juce::Slider::TextBoxRight, true, 40, 20);
    HighMidBandQualityKnobAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(mProcessor.apvts, "EQ_HIMID_BAND_QF", HighMidBandQualityKnob);
    HighMidBandQualityKnob.addListener(this);
    HighMidBandQualityKnob.setMinAndMaxValues(mProcessor.knobValueMap["EQ_HIMID_BAND_QF"].start, mProcessor.knobValueMap["EQ_HIMID_BAND_QF"].end);
    HighMidBandQualityKnob.setBounds(0, 20 * (i++), 120, 20);
    addAndMakeVisible(HighMidBandQualityKnob);

    HighBandGainKnobLabel.setText("High Band Gain", juce::NotificationType::dontSendNotification);
    HighBandGainKnobLabel.setBounds(0, 20 * (i++), 120, 20);
    addAndMakeVisible(HighBandGainKnobLabel);

    HighBandGainKnob.setSliderStyle(juce::Slider::SliderStyle::ThreeValueHorizontal);
    HighBandGainKnob.setTextBoxStyle(juce::Slider::TextBoxRight, true, 40, 20);
    HighBandGainKnobAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(mProcessor.apvts, "EQ_HI_BAND_GAIN", HighBandGainKnob);
    HighBandGainKnob.addListener(this);
    HighBandGainKnob.setMinAndMaxValues(mProcessor.knobValueMap["EQ_HI_BAND_GAIN"].start, mProcessor.knobValueMap["EQ_HI_BAND_GAIN"].end);
    HighBandGainKnob.setBounds(0, 20 * (i++), 120, 20);
    addAndMakeVisible(HighBandGainKnob);

    HighBandCutoffKnobLabel.setText("High Band Cutoff", juce::NotificationType::dontSendNotification);
    HighBandCutoffKnobLabel.setBounds(0, 20 * (i++), 120, 20);
    addAndMakeVisible(HighBandCutoffKnobLabel);

    HighBandCutoffKnob.setSliderStyle(juce::Slider::SliderStyle::ThreeValueHorizontal);
    HighBandCutoffKnob.setTextBoxStyle(juce::Slider::TextBoxRight, true, 40, 20);
    HighBandCutoffKnobAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(mProcessor.apvts, "EQ_HI_BAND_CUTOFF", HighBandCutoffKnob);
    HighBandCutoffKnob.addListener(this);
    HighBandCutoffKnob.setMinAndMaxValues(mProcessor.knobValueMap["EQ_HI_BAND_CUTOFF"].start, mProcessor.knobValueMap["EQ_HI_BAND_CUTOFF"].end);
    HighBandCutoffKnob.setBounds(0, 20 * (i++), 120, 20);
    addAndMakeVisible(HighBandCutoffKnob);

    HighBandQualityKnobLabel.setText("High Band Q", juce::NotificationType::dontSendNotification);
    HighBandQualityKnobLabel.setBounds(0, 20 * (i++), 120, 20);
    addAndMakeVisible(HighBandQualityKnobLabel);

    HighBandQualityKnob.setSliderStyle(juce::Slider::SliderStyle::ThreeValueHorizontal);
    HighBandQualityKnob.setTextBoxStyle(juce::Slider::TextBoxRight, true, 40, 20);
    HighBandQualityKnobAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(mProcessor.apvts, "EQ_HI_BAND_QF", HighBandQualityKnob);
    HighBandQualityKnob.addListener(this);
    HighBandQualityKnob.setMinAndMaxValues(mProcessor.knobValueMap["EQ_HI_BAND_QF"].start, mProcessor.knobValueMap["EQ_HI_BAND_QF"].end);
    HighBandQualityKnob.setBounds(0, 20 * (i++), 120, 20);
    addAndMakeVisible(HighBandQualityKnob);
}

EqualizerEditor::~EqualizerEditor()
{

}

void EqualizerEditor::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::seagreen);

    g.setColour(juce::Colours::white);
    g.setFont(15.0f);
    g.drawFittedText("Equalizer", getLocalBounds(), juce::Justification::centredTop, 1);
}

void EqualizerEditor::sliderValueChanged(juce::Slider* slider)
{
    if (slider == &PostGainKnob)
    {
        if (abs(PostGainKnob.getMinValue() - mProcessor.knobValueMap["EQ_POST_GAIN"].start) < 1e-3 || abs(PostGainKnob.getMaxValue() - mProcessor.knobValueMap["EQ_POST_GAIN"].end) < 1e-3)
            mProcessor.knobValueMap.set("EQ_POST_GAIN", ModdedNormalisableRange<float>(PostGainKnob.getMinValue(), PostGainKnob.getMaxValue()));
    }
    else if (slider == &LowBandGainKnob)
    {
        if (abs(LowBandGainKnob.getMinValue() - mProcessor.knobValueMap["EQ_LOW_BAND_GAIN"].start) < 1e-3 || abs(LowBandGainKnob.getMaxValue() - mProcessor.knobValueMap["EQ_LOW_BAND_GAIN"].end) < 1e-3)
            mProcessor.knobValueMap.set("EQ_LOW_BAND_GAIN", ModdedNormalisableRange<float>(LowBandGainKnob.getMinValue(), LowBandGainKnob.getMaxValue()));
    }
    else if (slider == &LowBandCutoffKnob)
    {
        if (abs(LowBandCutoffKnob.getMinValue() - mProcessor.knobValueMap["EQ_LOW_BAND_CUTOFF"].start) < 1e-3 || abs(LowBandCutoffKnob.getMaxValue() - mProcessor.knobValueMap["EQ_LOW_BAND_CUTOFF"].end) < 1e-3)
            mProcessor.knobValueMap.set("EQ_LOW_BAND_CUTOFF", ModdedNormalisableRange<float>(LowBandCutoffKnob.getMinValue(), LowBandCutoffKnob.getMaxValue()));
    }
    else if (slider == &LowBandQualityKnob)
    {
        if (abs(LowBandQualityKnob.getMinValue() - mProcessor.knobValueMap["EQ_LOW_BAND_QF"].start) < 1e-3 || abs(LowBandQualityKnob.getMaxValue() - mProcessor.knobValueMap["EQ_LOW_BAND_QF"].end) < 1e-3)
            mProcessor.knobValueMap.set("EQ_LOW_BAND_QF", ModdedNormalisableRange<float>(LowBandQualityKnob.getMinValue(), LowBandQualityKnob.getMaxValue()));
    }
    else if (slider == &LowMidBandGainKnob)
    {
        if (abs(LowMidBandGainKnob.getMinValue() - mProcessor.knobValueMap["EQ_LOWMID_BAND_GAIN"].start) < 1e-3 || abs(LowMidBandGainKnob.getMaxValue() - mProcessor.knobValueMap["EQ_LOWMID_BAND_GAIN"].end) < 1e-3)
            mProcessor.knobValueMap.set("EQ_LOWMID_BAND_GAIN", ModdedNormalisableRange<float>(LowMidBandGainKnob.getMinValue(), LowMidBandGainKnob.getMaxValue()));
    }
    else if (slider == &LowMidBandFreqKnob)
    {
        if (abs(LowMidBandFreqKnob.getMinValue() - mProcessor.knobValueMap["EQ_LOWMID_BAND_FREQ"].start) < 1e-3 || abs(LowMidBandFreqKnob.getMaxValue() - mProcessor.knobValueMap["EQ_LOWMID_BAND_FREQ"].end) < 1e-3)
            mProcessor.knobValueMap.set("EQ_LOWMID_BAND_FREQ", ModdedNormalisableRange<float>(LowMidBandFreqKnob.getMinValue(), LowMidBandFreqKnob.getMaxValue()));
    }
    else if (slider == &LowMidBandQualityKnob)
    {
        if (abs(LowMidBandQualityKnob.getMinValue() - mProcessor.knobValueMap["EQ_LOWMID_BAND_QF"].start) < 1e-3 || abs(LowMidBandQualityKnob.getMaxValue() - mProcessor.knobValueMap["EQ_LOWMID_BAND_QF"].end) < 1e-3)
            mProcessor.knobValueMap.set("EQ_LOWMID_BAND_QF", ModdedNormalisableRange<float>(LowMidBandQualityKnob.getMinValue(), LowMidBandQualityKnob.getMaxValue()));
    }
    else if (slider == &HighMidBandGainKnob)
    {
        if (abs(HighMidBandGainKnob.getMinValue() - mProcessor.knobValueMap["EQ_HIMID_BAND_GAIN"].start) < 1e-3 || abs(HighMidBandGainKnob.getMaxValue() - mProcessor.knobValueMap["EQ_HIMID_BAND_GAIN"].end) < 1e-3)
            mProcessor.knobValueMap.set("EQ_HIMID_BAND_GAIN", ModdedNormalisableRange<float>(HighMidBandGainKnob.getMinValue(), HighMidBandGainKnob.getMaxValue()));
    }
    else if (slider == &HighMidBandFreqKnob)
    {
        if (abs(HighMidBandFreqKnob.getMinValue() - mProcessor.knobValueMap["EQ_HIMID_BAND_FREQ"].start) < 1e-3 || abs(HighMidBandFreqKnob.getMaxValue() - mProcessor.knobValueMap["EQ_HIMID_BAND_FREQ"].end) < 1e-3)
            mProcessor.knobValueMap.set("EQ_HIMID_BAND_FREQ", ModdedNormalisableRange<float>(HighMidBandFreqKnob.getMinValue(), HighMidBandFreqKnob.getMaxValue()));
    }
    else if (slider == &HighMidBandQualityKnob)
    {
        if (abs(HighMidBandQualityKnob.getMinValue() - mProcessor.knobValueMap["EQ_HIMID_BAND_QF"].start) < 1e-3 || abs(HighMidBandQualityKnob.getMaxValue() - mProcessor.knobValueMap["EQ_HIMID_BAND_QF"].end) < 1e-3)
            mProcessor.knobValueMap.set("EQ_HIMID_BAND_QF", ModdedNormalisableRange<float>(HighMidBandQualityKnob.getMinValue(), HighMidBandQualityKnob.getMaxValue()));
    }
    else if (slider == &HighBandGainKnob)
    {
        if (abs(HighBandGainKnob.getMinValue() - mProcessor.knobValueMap["EQ_HI_BAND_GAIN"].start) < 1e-3 || abs(HighBandGainKnob.getMaxValue() - mProcessor.knobValueMap["EQ_HI_BAND_GAIN"].end) < 1e-3)
            mProcessor.knobValueMap.set("EQ_HI_BAND_GAIN", ModdedNormalisableRange<float>(HighBandGainKnob.getMinValue(), HighBandGainKnob.getMaxValue()));
    }
    else if (slider == &HighBandCutoffKnob)
    {
        if (abs(HighBandCutoffKnob.getMinValue() - mProcessor.knobValueMap["EQ_HI_BAND_CUTOFF"].start) < 1e-3 || abs(HighBandCutoffKnob.getMaxValue() - mProcessor.knobValueMap["EQ_HI_BAND_CUTOFF"].end) < 1e-3)
            mProcessor.knobValueMap.set("EQ_HI_BAND_CUTOFF", ModdedNormalisableRange<float>(HighBandCutoffKnob.getMinValue(), HighBandCutoffKnob.getMaxValue()));
    }
    else if (slider == &HighBandQualityKnob)
    {
        if (abs(HighBandQualityKnob.getMinValue() - mProcessor.knobValueMap["EQ_HI_BAND_QF"].start) < 1e-3 || abs(HighBandQualityKnob.getMaxValue() - mProcessor.knobValueMap["EQ_HI_BAND_QF"].end) < 1e-3)
            mProcessor.knobValueMap.set("EQ_HI_BAND_QF", ModdedNormalisableRange<float>(HighBandQualityKnob.getMinValue(), HighBandQualityKnob.getMaxValue()));
    }
}

void EqualizerEditor::updateRanges()
{
    PostGainKnob.setMinAndMaxValues(mProcessor.knobValueMap["EQ_POST_GAIN"].start, mProcessor.knobValueMap["EQ_POST_GAIN"].end);
    LowBandGainKnob.setMinAndMaxValues(mProcessor.knobValueMap["EQ_LOW_BAND_GAIN"].start, mProcessor.knobValueMap["EQ_LOW_BAND_GAIN"].end);
    LowBandCutoffKnob.setMinAndMaxValues(mProcessor.knobValueMap["EQ_LOW_BAND_CUTOFF"].start, mProcessor.knobValueMap["EQ_LOW_BAND_CUTOFF"].end);
    LowBandQualityKnob.setMinAndMaxValues(mProcessor.knobValueMap["EQ_LOW_BAND_QF"].start, mProcessor.knobValueMap["EQ_LOW_BAND_QF"].end);
    LowMidBandGainKnob.setMinAndMaxValues(mProcessor.knobValueMap["EQ_LOWMID_BAND_GAIN"].start, mProcessor.knobValueMap["EQ_LOWMID_BAND_GAIN"].end);
    LowMidBandFreqKnob.setMinAndMaxValues(mProcessor.knobValueMap["EQ_LOWMID_BAND_FREQ"].start, mProcessor.knobValueMap["EQ_LOWMID_BAND_FREQ"].end);
    LowMidBandQualityKnob.setMinAndMaxValues(mProcessor.knobValueMap["EQ_LOWMID_BAND_QF"].start, mProcessor.knobValueMap["EQ_LOWMID_BAND_QF"].end);
    HighMidBandGainKnob.setMinAndMaxValues(mProcessor.knobValueMap["EQ_HIMID_BAND_GAIN"].start, mProcessor.knobValueMap["EQ_HIMID_BAND_GAIN"].end);
    HighMidBandFreqKnob.setMinAndMaxValues(mProcessor.knobValueMap["EQ_HIMID_BAND_FREQ"].start, mProcessor.knobValueMap["EQ_HIMID_BAND_FREQ"].end);
    HighMidBandQualityKnob.setMinAndMaxValues(mProcessor.knobValueMap["EQ_HIMID_BAND_QF"].start, mProcessor.knobValueMap["EQ_HIMID_BAND_QF"].end);
    HighBandGainKnob.setMinAndMaxValues(mProcessor.knobValueMap["EQ_HI_BAND_GAIN"].start, mProcessor.knobValueMap["EQ_HI_BAND_GAIN"].end);
    HighBandCutoffKnob.setMinAndMaxValues(mProcessor.knobValueMap["EQ_HI_BAND_CUTOFF"].start, mProcessor.knobValueMap["EQ_HI_BAND_CUTOFF"].end);
    HighBandQualityKnob.setMinAndMaxValues(mProcessor.knobValueMap["EQ_HI_BAND_QF"].start, mProcessor.knobValueMap["EQ_HI_BAND_QF"].end);
}   