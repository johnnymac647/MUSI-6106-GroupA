/*
  ==============================================================================

    ReverbEditor.cpp
    Created: 6 Feb 2022 4:51:25pm
    Author:  yinsile

  ==============================================================================
*/

#include "ReverbEditor.h"

ReverbEditor::ReverbEditor(Reverb& p)
    :AudioProcessorEditor(&p), mProcessor(p)
{
    PostGainLabel.setText("Post Gain", juce::NotificationType::dontSendNotification);
    PostGainLabel.setBounds(0, 20, 120, 20);
    addAndMakeVisible(PostGainLabel);

    PostGainKnob.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    PostGainKnob.setTextBoxStyle(juce::Slider::TextBoxRight, true, 40, 20);
    PostGainKnobAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(*(mProcessor.ptr_apvts), "REVERB_POST_GAIN", PostGainKnob);
    PostGainKnob.setBounds(0, 40, 120, 20);
    addAndMakeVisible(PostGainKnob);

    RoomSizeLabel.setText("Room Size", juce::NotificationType::dontSendNotification);
    RoomSizeLabel.setBounds(0, 60, 120, 20);
    addAndMakeVisible(RoomSizeLabel);

    RoomSizeKnob.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    RoomSizeKnob.setTextBoxStyle(juce::Slider::TextBoxRight, true, 40, 20);
    RoomSizeKnobAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(*(mProcessor.ptr_apvts), "REVERB_ROOM_SIZE", RoomSizeKnob);
    RoomSizeKnob.setBounds(0, 80, 120, 20);
    addAndMakeVisible(RoomSizeKnob);

    DampingLabel.setText("Damping", juce::NotificationType::dontSendNotification);
    DampingLabel.setBounds(0, 100, 120, 20);
    addAndMakeVisible(DampingLabel);

    DampingKnob.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    DampingKnob.setTextBoxStyle(juce::Slider::TextBoxRight, true, 40, 20);
    DampingKnobAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(*(mProcessor.ptr_apvts), "REVERB_DAMPING", DampingKnob);
    DampingKnob.setBounds(0, 120, 120, 20);
    addAndMakeVisible(DampingKnob);

    WetLevelLabel.setText("Wet Level", juce::NotificationType::dontSendNotification);
    WetLevelLabel.setBounds(0, 140, 120, 20);
    addAndMakeVisible(WetLevelLabel);

    WetLevelKnob.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    WetLevelKnob.setTextBoxStyle(juce::Slider::TextBoxRight, true, 40, 20);
    WetLevelKnobAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(*(mProcessor.ptr_apvts), "REVERB_WET_LEVEL", WetLevelKnob);
    WetLevelKnob.setBounds(0, 160, 120, 20);
    addAndMakeVisible(WetLevelKnob);

    DryLevelLabel.setText("Dry Level", juce::NotificationType::dontSendNotification);
    DryLevelLabel.setBounds(0, 180, 120, 20);
    addAndMakeVisible(DryLevelLabel);

    DryLevelKnob.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    DryLevelKnob.setTextBoxStyle(juce::Slider::TextBoxRight, true, 40, 20);
    DryLevelKnobAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(*(mProcessor.ptr_apvts), "REVERB_DRY_LEVEL", DryLevelKnob);
    DryLevelKnob.setBounds(0, 200, 120, 20);
    addAndMakeVisible(DryLevelKnob);

    WidthLabel.setText("Width", juce::NotificationType::dontSendNotification);
    WidthLabel.setBounds(0, 220, 120, 20);
    addAndMakeVisible(WidthLabel);

    WidthKnob.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    WidthKnob.setTextBoxStyle(juce::Slider::TextBoxRight, true, 40, 20);
    WidthKnobAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(*(mProcessor.ptr_apvts), "REVERB_WIDTH", WidthKnob);
    WidthKnob.setBounds(0, 240, 120, 20);
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