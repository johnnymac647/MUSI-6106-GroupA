/*
  ==============================================================================

    ReverbEditor.cpp
    Created: 6 Feb 2022 4:51:25pm
    Author:  yinsile

  ==============================================================================
*/

#include "ReverbEditor.h"

ReverbEditor::ReverbEditor(OneKnobVocalAudioProcessor& p)
    :AudioProcessorEditor(&p), mProcessor(p)
{
    int i = 1;

    PostGainLabel.setText("Post Gain", juce::NotificationType::dontSendNotification);
    PostGainLabel.setBounds(0, 20 * (i++), 120, 20);
    addAndMakeVisible(PostGainLabel);

    PostGainKnob.setSliderStyle(juce::Slider::SliderStyle::ThreeValueHorizontal);
    PostGainKnob.setTextBoxStyle(juce::Slider::TextBoxRight, true, 40, 20);
    PostGainKnobAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(mProcessor.apvts, "REVERB_POST_GAIN", PostGainKnob);
    PostGainKnob.addListener(this);
    PostGainKnob.setMinAndMaxValues(mProcessor.knobValueMap["REVERB_POST_GAIN"].start, mProcessor.knobValueMap["REVERB_POST_GAIN"].end);
    PostGainKnob.setBounds(0, 20 * (i++), 120, 20);
    addAndMakeVisible(PostGainKnob);

    RoomSizeLabel.setText("Room Size", juce::NotificationType::dontSendNotification);
    RoomSizeLabel.setBounds(0, 20 * (i++), 120, 20);
    addAndMakeVisible(RoomSizeLabel);

    RoomSizeKnob.setSliderStyle(juce::Slider::SliderStyle::ThreeValueHorizontal);
    RoomSizeKnob.setTextBoxStyle(juce::Slider::TextBoxRight, true, 40, 20);
    RoomSizeKnobAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(mProcessor.apvts, "REVERB_ROOM_SIZE", RoomSizeKnob);
    RoomSizeKnob.addListener(this);
    RoomSizeKnob.setMinAndMaxValues(mProcessor.knobValueMap["REVERB_ROOM_SIZE"].start, mProcessor.knobValueMap["REVERB_ROOM_SIZE"].end);
    RoomSizeKnob.setBounds(0, 20 * (i++), 120, 20);
    addAndMakeVisible(RoomSizeKnob);

    DampingLabel.setText("Damping", juce::NotificationType::dontSendNotification);
    DampingLabel.setBounds(0, 20 * (i++), 120, 20);
    addAndMakeVisible(DampingLabel);

    DampingKnob.setSliderStyle(juce::Slider::SliderStyle::ThreeValueHorizontal);
    DampingKnob.setTextBoxStyle(juce::Slider::TextBoxRight, true, 40, 20);
    DampingKnobAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(mProcessor.apvts, "REVERB_DAMPING", DampingKnob);
    DampingKnob.addListener(this);
    DampingKnob.setMinAndMaxValues(mProcessor.knobValueMap["REVERB_DAMPING"].start, mProcessor.knobValueMap["REVERB_DAMPING"].end);
    DampingKnob.setBounds(0, 20 * (i++), 120, 20);
    addAndMakeVisible(DampingKnob);

    WetLevelLabel.setText("Wet Level", juce::NotificationType::dontSendNotification);
    WetLevelLabel.setBounds(0, 20 * (i++), 120, 20);
    addAndMakeVisible(WetLevelLabel);

    WetLevelKnob.setSliderStyle(juce::Slider::SliderStyle::ThreeValueHorizontal);
    WetLevelKnob.setTextBoxStyle(juce::Slider::TextBoxRight, true, 40, 20);
    WetLevelKnobAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(mProcessor.apvts, "REVERB_WET_LEVEL", WetLevelKnob);
    WetLevelKnob.addListener(this);
    WetLevelKnob.setMinAndMaxValues(mProcessor.knobValueMap["REVERB_WET_LEVEL"].start, mProcessor.knobValueMap["REVERB_WET_LEVEL"].end);
    WetLevelKnob.setBounds(0, 20 * (i++), 120, 20);
    addAndMakeVisible(WetLevelKnob);

    DryLevelLabel.setText("Dry Level", juce::NotificationType::dontSendNotification);
    DryLevelLabel.setBounds(0, 20 * (i++), 120, 20);
    addAndMakeVisible(DryLevelLabel);

    DryLevelKnob.setSliderStyle(juce::Slider::SliderStyle::ThreeValueHorizontal);
    DryLevelKnob.setTextBoxStyle(juce::Slider::TextBoxRight, true, 40, 20);
    DryLevelKnobAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(mProcessor.apvts, "REVERB_DRY_LEVEL", DryLevelKnob);
    DryLevelKnob.addListener(this);
    DryLevelKnob.setMinAndMaxValues(mProcessor.knobValueMap["REVERB_DRY_LEVEL"].start, mProcessor.knobValueMap["REVERB_DRY_LEVEL"].end);
    DryLevelKnob.setBounds(0, 20 * (i++), 120, 20);
    addAndMakeVisible(DryLevelKnob);

    WidthLabel.setText("Width", juce::NotificationType::dontSendNotification);
    WidthLabel.setBounds(0, 20 * (i++), 120, 20);
    addAndMakeVisible(WidthLabel);

    WidthKnob.setSliderStyle(juce::Slider::SliderStyle::ThreeValueHorizontal);
    WidthKnob.setTextBoxStyle(juce::Slider::TextBoxRight, true, 40, 20);
    WidthKnobAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(mProcessor.apvts, "REVERB_WIDTH", WidthKnob);
    WidthKnob.addListener(this);
    WidthKnob.setMinAndMaxValues(mProcessor.knobValueMap["REVERB_WIDTH"].start, mProcessor.knobValueMap["REVERB_WIDTH"].end);
    WidthKnob.setBounds(0, 20 * (i++), 120, 20);
    addAndMakeVisible(WidthKnob);

}
ReverbEditor::~ReverbEditor()
{

}
void ReverbEditor::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::silver);

    g.setColour(juce::Colours::white);
    g.setFont(15.0f);
    g.drawFittedText("Reverb", getLocalBounds(), juce::Justification::centredTop, 1);
}

void ReverbEditor::sliderValueChanged(juce::Slider* slider)
{
    if (slider == &PostGainKnob)
    {
        if (abs(PostGainKnob.getMinValue() - mProcessor.knobValueMap["REVERB_POST_GAIN"].start) < 1e-3 || abs(PostGainKnob.getMaxValue() - mProcessor.knobValueMap["REVERB_POST_GAIN"].end) < 1e-3)
            mProcessor.knobValueMap.set("REVERB_POST_GAIN", ModdedNormalisableRange<float>(PostGainKnob.getMinValue(), PostGainKnob.getMaxValue()));
    }
    else if (slider == &RoomSizeKnob)
    {
        if (abs(RoomSizeKnob.getMinValue() - mProcessor.knobValueMap["REVERB_ROOM_SIZE"].start) < 1e-3 || abs(RoomSizeKnob.getMaxValue() - mProcessor.knobValueMap["REVERB_ROOM_SIZE"].end) < 1e-3)
            mProcessor.knobValueMap.set("REVERB_ROOM_SIZE", ModdedNormalisableRange<float>(RoomSizeKnob.getMinValue(), RoomSizeKnob.getMaxValue()));
    }
    else if (slider == &DampingKnob)
    {
        if (abs(DampingKnob.getMinValue() - mProcessor.knobValueMap["REVERB_DAMPING"].start) < 1e-3 || abs(DampingKnob.getMaxValue() - mProcessor.knobValueMap["REVERB_DAMPING"].end) < 1e-3)
            mProcessor.knobValueMap.set("REVERB_DAMPING", ModdedNormalisableRange<float>(DampingKnob.getMinValue(), DampingKnob.getMaxValue()));
    }
    else if (slider == &WetLevelKnob)
    {
        if (abs(WetLevelKnob.getMinValue() - mProcessor.knobValueMap["REVERB_WET_LEVEL"].start) < 1e-3 || abs(WetLevelKnob.getMaxValue() - mProcessor.knobValueMap["REVERB_WET_LEVEL"].end) < 1e-3)
            mProcessor.knobValueMap.set("REVERB_WET_LEVEL", ModdedNormalisableRange<float>(WetLevelKnob.getMinValue(), WetLevelKnob.getMaxValue()));
    }
    else if (slider == &DryLevelKnob)
    {
        if (abs(DryLevelKnob.getMinValue() - mProcessor.knobValueMap["REVERB_DRY_LEVEL"].start) < 1e-3 || abs(DryLevelKnob.getMaxValue() - mProcessor.knobValueMap["REVERB_DRY_LEVEL"].end) < 1e-3)
            mProcessor.knobValueMap.set("REVERB_DRY_LEVEL", ModdedNormalisableRange<float>(DryLevelKnob.getMinValue(), DryLevelKnob.getMaxValue()));
    }
    else if (slider == &WidthKnob)
    {
        if (abs(WidthKnob.getMinValue() - mProcessor.knobValueMap["REVERB_WIDTH"].start) < 1e-3 || abs(WidthKnob.getMaxValue() - mProcessor.knobValueMap["REVERB_WIDTH"].end) < 1e-3)
            mProcessor.knobValueMap.set("REVERB_WIDTH", ModdedNormalisableRange<float>(WidthKnob.getMinValue(), WidthKnob.getMaxValue()));
    }
}

void ReverbEditor::updateRanges()
{
    PostGainKnob.setMinAndMaxValues(mProcessor.knobValueMap["REVERB_POST_GAIN"].start, mProcessor.knobValueMap["REVERB_POST_GAIN"].end);
    RoomSizeKnob.setMinAndMaxValues(mProcessor.knobValueMap["REVERB_ROOM_SIZE"].start, mProcessor.knobValueMap["REVERB_ROOM_SIZE"].end);
    DampingKnob.setMinAndMaxValues(mProcessor.knobValueMap["REVERB_DAMPING"].start, mProcessor.knobValueMap["REVERB_DAMPING"].end);
    WetLevelKnob.setMinAndMaxValues(mProcessor.knobValueMap["REVERB_WET_LEVEL"].start, mProcessor.knobValueMap["REVERB_WET_LEVEL"].end);
    DryLevelKnob.setMinAndMaxValues(mProcessor.knobValueMap["REVERB_DRY_LEVEL"].start, mProcessor.knobValueMap["REVERB_DRY_LEVEL"].end);
    WidthKnob.setMinAndMaxValues(mProcessor.knobValueMap["REVERB_WIDTH"].start, mProcessor.knobValueMap["REVERB_WIDTH"].end);
}