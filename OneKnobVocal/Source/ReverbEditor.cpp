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
    PostGainKnob.setMinAndMaxValues(mProcessor.knobValueMap["REVERB_POST_GAIN"].start, mProcessor.knobValueMap["REVERB_POST_GAIN"].end);
    PostGainKnob.setBounds(0, 20 * (i++), 120, 20);
    addAndMakeVisible(PostGainKnob);

    RoomSizeLabel.setText("Room Size", juce::NotificationType::dontSendNotification);
    RoomSizeLabel.setBounds(0, 20 * (i++), 120, 20);
    addAndMakeVisible(RoomSizeLabel);

    RoomSizeKnob.setSliderStyle(juce::Slider::SliderStyle::ThreeValueHorizontal);
    RoomSizeKnob.setTextBoxStyle(juce::Slider::TextBoxRight, true, 40, 20);
    RoomSizeKnobAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(mProcessor.apvts, "REVERB_ROOM_SIZE", RoomSizeKnob);
    RoomSizeKnob.setMinAndMaxValues(mProcessor.knobValueMap["REVERB_ROOM_SIZE"].start, mProcessor.knobValueMap["REVERB_ROOM_SIZE"].end);
    RoomSizeKnob.setBounds(0, 20 * (i++), 120, 20);
    addAndMakeVisible(RoomSizeKnob);

    DampingLabel.setText("Damping", juce::NotificationType::dontSendNotification);
    DampingLabel.setBounds(0, 20 * (i++), 120, 20);
    addAndMakeVisible(DampingLabel);

    DampingKnob.setSliderStyle(juce::Slider::SliderStyle::ThreeValueHorizontal);
    DampingKnob.setTextBoxStyle(juce::Slider::TextBoxRight, true, 40, 20);
    DampingKnobAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(mProcessor.apvts, "REVERB_DAMPING", DampingKnob);
    DampingKnob.setMinAndMaxValues(mProcessor.knobValueMap["REVERB_DAMPING"].start, mProcessor.knobValueMap["REVERB_DAMPING"].end);
    DampingKnob.setBounds(0, 20 * (i++), 120, 20);
    addAndMakeVisible(DampingKnob);

    WetLevelLabel.setText("Wet Level", juce::NotificationType::dontSendNotification);
    WetLevelLabel.setBounds(0, 20 * (i++), 120, 20);
    addAndMakeVisible(WetLevelLabel);

    WetLevelKnob.setSliderStyle(juce::Slider::SliderStyle::ThreeValueHorizontal);
    WetLevelKnob.setTextBoxStyle(juce::Slider::TextBoxRight, true, 40, 20);
    WetLevelKnobAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(mProcessor.apvts, "REVERB_WET_LEVEL", WetLevelKnob);
    WetLevelKnob.setMinAndMaxValues(mProcessor.knobValueMap["REVERB_WET_LEVEL"].start, mProcessor.knobValueMap["REVERB_WET_LEVEL"].end);
    WetLevelKnob.setBounds(0, 20 * (i++), 120, 20);
    addAndMakeVisible(WetLevelKnob);

    DryLevelLabel.setText("Dry Level", juce::NotificationType::dontSendNotification);
    DryLevelLabel.setBounds(0, 20 * (i++), 120, 20);
    addAndMakeVisible(DryLevelLabel);

    DryLevelKnob.setSliderStyle(juce::Slider::SliderStyle::ThreeValueHorizontal);
    DryLevelKnob.setTextBoxStyle(juce::Slider::TextBoxRight, true, 40, 20);
    DryLevelKnobAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(mProcessor.apvts, "REVERB_DRY_LEVEL", DryLevelKnob);
    DryLevelKnob.setMinAndMaxValues(mProcessor.knobValueMap["REVERB_DRY_LEVEL"].start, mProcessor.knobValueMap["REVERB_DRY_LEVEL"].end);
    DryLevelKnob.setBounds(0, 20 * (i++), 120, 20);
    addAndMakeVisible(DryLevelKnob);

    WidthLabel.setText("Width", juce::NotificationType::dontSendNotification);
    WidthLabel.setBounds(0, 20 * (i++), 120, 20);
    addAndMakeVisible(WidthLabel);

    WidthKnob.setSliderStyle(juce::Slider::SliderStyle::ThreeValueHorizontal);
    WidthKnob.setTextBoxStyle(juce::Slider::TextBoxRight, true, 40, 20);
    WidthKnobAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(mProcessor.apvts, "REVERB_WIDTH", WidthKnob);
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