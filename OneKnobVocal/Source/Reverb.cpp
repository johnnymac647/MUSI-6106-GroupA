/*
  ==============================================================================

    Reverb.cpp
    Created: 2 Feb 2022 11:39:18pm
    Author:  yinsile

  ==============================================================================
*/

#include "Reverb.h"

void Reverb::getReverbParameters(const juce::AudioProcessorValueTreeState& apvts)
{
    juce::Reverb::Parameters reverbParam;

    reverbParam.roomSize = apvts.getRawParameterValue("REVERB_ROOM_SIZE")->load();
    reverbParam.damping = apvts.getRawParameterValue("REVERB_DAMPING")->load();
    reverbParam.wetLevel = juce::Decibels::decibelsToGain<float>(apvts.getRawParameterValue("REVERB_WET_LEVEL")->load());
    reverbParam.dryLevel = juce::Decibels::decibelsToGain<float>(apvts.getRawParameterValue("REVERB_DRY_LEVEL")->load());
    reverbParam.width = apvts.getRawParameterValue("REVERB_WIDTH")->load();

    reverb.setParameters(reverbParam);
}