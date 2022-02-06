/*
  ==============================================================================

    GainSlider.h
    Created: 6 Feb 2022 4:00:42pm
    Author:  yinsile

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Gain.h"

class GainSlider : public juce::AudioProcessorEditor
{
public:
    GainSlider(Gain&, juce::Colour c=juce::Colours::lightblue);
    ~GainSlider() override;
    void paint(juce::Graphics&) override;
private:
    Gain& mProcessor;
    juce::Colour mBackgroundColour;
    juce::Slider VolumeKnob;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> VolumeKnobAttach;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GainSlider);
};
