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

    reverbParam.roomSize = apvts.getRawParameterValue(parameterIDs[kRoomSize])->load();
    reverbParam.damping = apvts.getRawParameterValue(parameterIDs[kDamping])->load();
    reverbParam.wetLevel = juce::Decibels::decibelsToGain<float>(apvts.getRawParameterValue(parameterIDs[kWetLevel])->load());
    reverbParam.dryLevel = juce::Decibels::decibelsToGain<float>(apvts.getRawParameterValue(parameterIDs[kDryLevel])->load());
    reverbParam.width = apvts.getRawParameterValue(parameterIDs[kWidth])->load();

    reverb.setParameters(reverbParam);
}