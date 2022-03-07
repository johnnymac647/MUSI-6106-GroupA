/*
  ==============================================================================

    ReverbEditor.h
    Created: 6 Feb 2022 4:51:25pm
    Author:  yinsile

  ==============================================================================
*/

#pragma once
#include "Reverb.h"

class ReverbEditor : public juce::AudioProcessorEditor
{
public:
    ReverbEditor(Reverb&);
    ~ReverbEditor();
    void paint(juce::Graphics&) override;
private:
    Reverb& mProcessor;

    
    juce::Slider PostGainKnob;
    juce::Label PostGainLabel;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> PostGainKnobAttach;

    juce::Slider RoomSizeKnob;
    juce::Label RoomSizeLabel;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> RoomSizeKnobAttach;

    juce::Slider DampingKnob;
    juce::Label DampingLabel;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> DampingKnobAttach;

    juce::Slider WetLevelKnob;
    juce::Label WetLevelLabel;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> WetLevelKnobAttach;

    juce::Slider DryLevelKnob;
    juce::Label DryLevelLabel;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> DryLevelKnobAttach;

    juce::Slider WidthKnob;
    juce::Label WidthLabel;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> WidthKnobAttach;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ReverbEditor);
};