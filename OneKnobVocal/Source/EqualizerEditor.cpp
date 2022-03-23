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
    PostGainKnob.setMinAndMaxValues(mProcessor.knobValueMap["EQ_POST_GAIN"].start, mProcessor.knobValueMap["EQ_POST_GAIN"].end);
    PostGainKnob.setBounds(0, 20 * (i++), 120, 20);
    addAndMakeVisible(PostGainKnob);

    LowBandGainKnobLabel.setText("Low Band Gain", juce::NotificationType::dontSendNotification);
    LowBandGainKnobLabel.setBounds(0, 20 * (i++), 120, 20);
    addAndMakeVisible(LowBandGainKnobLabel);

    LowBandGainKnob.setSliderStyle(juce::Slider::SliderStyle::ThreeValueHorizontal);
    LowBandGainKnob.setTextBoxStyle(juce::Slider::TextBoxRight, true, 40, 20);
    LowBandGainKnobAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(mProcessor.apvts, "EQ_LOW_BAND_GAIN", LowBandGainKnob);
    LowBandGainKnob.setMinAndMaxValues(mProcessor.knobValueMap["EQ_LOW_BAND_GAIN"].start, mProcessor.knobValueMap["EQ_LOW_BAND_GAIN"].end);
    LowBandGainKnob.setBounds(0, 20 * (i++), 120, 20);
    addAndMakeVisible(LowBandGainKnob);

    LowBandCutoffKnobLabel.setText("Low Band Cutoff", juce::NotificationType::dontSendNotification);
    LowBandCutoffKnobLabel.setBounds(0, 20 * (i++), 120, 20);
    addAndMakeVisible(LowBandCutoffKnobLabel);

    LowBandCutoffKnob.setSliderStyle(juce::Slider::SliderStyle::ThreeValueHorizontal);
    LowBandCutoffKnob.setTextBoxStyle(juce::Slider::TextBoxRight, true, 40, 20);
    LowBandCutoffKnobAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(mProcessor.apvts, "EQ_LOW_BAND_CUTOFF", LowBandCutoffKnob);
    LowBandCutoffKnob.setMinAndMaxValues(mProcessor.knobValueMap["EQ_LOW_BAND_CUTOFF"].start, mProcessor.knobValueMap["EQ_LOW_BAND_CUTOFF"].end);
    LowBandCutoffKnob.setBounds(0, 20 * (i++), 120, 20);
    addAndMakeVisible(LowBandCutoffKnob);

    LowBandQualityKnobLabel.setText("Low Band Q", juce::NotificationType::dontSendNotification);
    LowBandQualityKnobLabel.setBounds(0, 20 * (i++), 120, 20);
    addAndMakeVisible(LowBandQualityKnobLabel);

    LowBandQualityKnob.setSliderStyle(juce::Slider::SliderStyle::ThreeValueHorizontal);
    LowBandQualityKnob.setTextBoxStyle(juce::Slider::TextBoxRight, true, 40, 20);
    LowBandQualityKnobAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(mProcessor.apvts, "EQ_LOW_BAND_QF", LowBandQualityKnob);
    LowBandQualityKnob.setMinAndMaxValues(mProcessor.knobValueMap["EQ_LOW_BAND_QF"].start, mProcessor.knobValueMap["EQ_LOW_BAND_QF"].end);
    LowBandQualityKnob.setBounds(0, 20 * (i++), 120, 20);
    addAndMakeVisible(LowBandQualityKnob);

    LowMidBandGainKnobLabel.setText("Low-mid Band Gain", juce::NotificationType::dontSendNotification);
    LowMidBandGainKnobLabel.setBounds(0, 20 * (i++), 120, 20);
    addAndMakeVisible(LowMidBandGainKnobLabel);

    LowMidBandGainKnob.setSliderStyle(juce::Slider::SliderStyle::ThreeValueHorizontal);
    LowMidBandGainKnob.setTextBoxStyle(juce::Slider::TextBoxRight, true, 40, 20);
    LowMidBandGainKnobAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(mProcessor.apvts, "EQ_LOWMID_BAND_GAIN", LowMidBandGainKnob);
    LowMidBandGainKnob.setMinAndMaxValues(mProcessor.knobValueMap["EQ_LOWMID_BAND_GAIN"].start, mProcessor.knobValueMap["EQ_LOWMID_BAND_GAIN"].end);
    LowMidBandGainKnob.setBounds(0, 20 * (i++), 120, 20);
    addAndMakeVisible(LowMidBandGainKnob);

    LowMidBandFreqKnobLabel.setText("Low-mid Band Freq", juce::NotificationType::dontSendNotification);
    LowMidBandFreqKnobLabel.setBounds(0, 20 * (i++), 120, 20);
    addAndMakeVisible(LowMidBandFreqKnobLabel);

    LowMidBandFreqKnob.setSliderStyle(juce::Slider::SliderStyle::ThreeValueHorizontal);
    LowMidBandFreqKnob.setTextBoxStyle(juce::Slider::TextBoxRight, true, 40, 20);
    LowMidBandFreqKnobAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(mProcessor.apvts, "EQ_LOWMID_BAND_FREQ", LowMidBandFreqKnob);
    LowMidBandFreqKnob.setMinAndMaxValues(mProcessor.knobValueMap["EQ_LOWMID_BAND_FREQ"].start, mProcessor.knobValueMap["EQ_LOWMID_BAND_FREQ"].end);
    LowMidBandFreqKnob.setBounds(0, 20 * (i++), 120, 20);
    addAndMakeVisible(LowMidBandFreqKnob);

    LowMidBandQualityKnobLabel.setText("Low-mid Band Q", juce::NotificationType::dontSendNotification);
    LowMidBandQualityKnobLabel.setBounds(0, 20 * (i++), 120, 20);
    addAndMakeVisible(LowMidBandQualityKnobLabel);

    LowMidBandQualityKnob.setSliderStyle(juce::Slider::SliderStyle::ThreeValueHorizontal);
    LowMidBandQualityKnob.setTextBoxStyle(juce::Slider::TextBoxRight, true, 40, 20);
    LowMidBandQualityKnobAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(mProcessor.apvts, "EQ_LOWMID_BAND_QF", LowMidBandQualityKnob);
    LowMidBandQualityKnob.setMinAndMaxValues(mProcessor.knobValueMap["EQ_LOWMID_BAND_QF"].start, mProcessor.knobValueMap["EQ_LOWMID_BAND_QF"].end);
    LowMidBandQualityKnob.setBounds(0, 20 * (i++), 120, 20);
    addAndMakeVisible(LowMidBandQualityKnob);

    HighMidBandGainKnobLabel.setText("High-mid Band Gain", juce::NotificationType::dontSendNotification);
    HighMidBandGainKnobLabel.setBounds(0, 20 * (i++), 120, 20);
    addAndMakeVisible(HighMidBandGainKnobLabel);

    HighMidBandGainKnob.setSliderStyle(juce::Slider::SliderStyle::ThreeValueHorizontal);
    HighMidBandGainKnob.setTextBoxStyle(juce::Slider::TextBoxRight, true, 40, 20);
    HighMidBandGainKnobAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(mProcessor.apvts, "EQ_HIMID_BAND_GAIN", HighMidBandGainKnob);
    HighMidBandGainKnob.setMinAndMaxValues(mProcessor.knobValueMap["EQ_HIMID_BAND_GAIN"].start, mProcessor.knobValueMap["EQ_HIMID_BAND_GAIN"].end);
    HighMidBandGainKnob.setBounds(0, 20 * (i++), 120, 20);
    addAndMakeVisible(HighMidBandGainKnob);

    HighMidBandFreqKnobLabel.setText("High-mid Band Freq", juce::NotificationType::dontSendNotification);
    HighMidBandFreqKnobLabel.setBounds(0, 20 * (i++), 120, 20);
    addAndMakeVisible(HighMidBandFreqKnobLabel);

    HighMidBandFreqKnob.setSliderStyle(juce::Slider::SliderStyle::ThreeValueHorizontal);
    HighMidBandFreqKnob.setTextBoxStyle(juce::Slider::TextBoxRight, true, 40, 20);
    HighMidBandFreqKnobAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(mProcessor.apvts, "EQ_HIMID_BAND_FREQ", HighMidBandFreqKnob);
    HighMidBandFreqKnob.setMinAndMaxValues(mProcessor.knobValueMap["EQ_HIMID_BAND_FREQ"].start, mProcessor.knobValueMap["EQ_HIMID_BAND_FREQ"].end);
    HighMidBandFreqKnob.setBounds(0, 20 * (i++), 120, 20);
    addAndMakeVisible(HighMidBandFreqKnob);

    HighMidBandQualityKnobLabel.setText("High-mid Band Q", juce::NotificationType::dontSendNotification);
    HighMidBandQualityKnobLabel.setBounds(0, 20 * (i++), 120, 20);
    addAndMakeVisible(HighMidBandQualityKnobLabel);

    HighMidBandQualityKnob.setSliderStyle(juce::Slider::SliderStyle::ThreeValueHorizontal);
    HighMidBandQualityKnob.setTextBoxStyle(juce::Slider::TextBoxRight, true, 40, 20);
    HighMidBandQualityKnobAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(mProcessor.apvts, "EQ_HIMID_BAND_QF", HighMidBandQualityKnob);
    HighMidBandQualityKnob.setMinAndMaxValues(mProcessor.knobValueMap["EQ_HIMID_BAND_QF"].start, mProcessor.knobValueMap["EQ_HIMID_BAND_QF"].end);
    HighMidBandQualityKnob.setBounds(0, 20 * (i++), 120, 20);
    addAndMakeVisible(HighMidBandQualityKnob);

    HighBandGainKnobLabel.setText("High Band Gain", juce::NotificationType::dontSendNotification);
    HighBandGainKnobLabel.setBounds(0, 20 * (i++), 120, 20);
    addAndMakeVisible(HighBandGainKnobLabel);

    HighBandGainKnob.setSliderStyle(juce::Slider::SliderStyle::ThreeValueHorizontal);
    HighBandGainKnob.setTextBoxStyle(juce::Slider::TextBoxRight, true, 40, 20);
    HighBandGainKnobAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(mProcessor.apvts, "EQ_HI_BAND_GAIN", HighBandGainKnob);
    HighBandGainKnob.setMinAndMaxValues(mProcessor.knobValueMap["EQ_HI_BAND_GAIN"].start, mProcessor.knobValueMap["EQ_HI_BAND_GAIN"].end);
    HighBandGainKnob.setBounds(0, 20 * (i++), 120, 20);
    addAndMakeVisible(HighBandGainKnob);

    HighBandCutoffKnobLabel.setText("High Band Cutoff", juce::NotificationType::dontSendNotification);
    HighBandCutoffKnobLabel.setBounds(0, 20 * (i++), 120, 20);
    addAndMakeVisible(HighBandCutoffKnobLabel);

    HighBandCutoffKnob.setSliderStyle(juce::Slider::SliderStyle::ThreeValueHorizontal);
    HighBandCutoffKnob.setTextBoxStyle(juce::Slider::TextBoxRight, true, 40, 20);
    HighBandCutoffKnobAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(mProcessor.apvts, "EQ_HI_BAND_CUTOFF", HighBandCutoffKnob);
    HighBandCutoffKnob.setMinAndMaxValues(mProcessor.knobValueMap["EQ_HI_BAND_CUTOFF"].start, mProcessor.knobValueMap["EQ_HI_BAND_CUTOFF"].end);
    HighBandCutoffKnob.setBounds(0, 20 * (i++), 120, 20);
    addAndMakeVisible(HighBandCutoffKnob);

    HighBandQualityKnobLabel.setText("High Band Q", juce::NotificationType::dontSendNotification);
    HighBandQualityKnobLabel.setBounds(0, 20 * (i++), 120, 20);
    addAndMakeVisible(HighBandQualityKnobLabel);

    HighBandQualityKnob.setSliderStyle(juce::Slider::SliderStyle::ThreeValueHorizontal);
    HighBandQualityKnob.setTextBoxStyle(juce::Slider::TextBoxRight, true, 40, 20);
    HighBandQualityKnobAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(mProcessor.apvts, "EQ_HI_BAND_QF", HighBandQualityKnob);
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