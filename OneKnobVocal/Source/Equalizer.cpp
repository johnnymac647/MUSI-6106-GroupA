/*
  ==============================================================================

    Equalizer.cpp
    Created: 2 Feb 2022 11:38:40pm
    Author:  yinsile

  ==============================================================================
*/

#include "Equalizer.h"

Equalizer::EQSettings Equalizer::getEQSettings(const juce::AudioProcessorValueTreeState& apvts){
    EQSettings settings;
    
    settings.postGainDecibels = apvts.getRawParameterValue(parameterIDs[kPostGain])->load();
    settings.lowGainDecibels = apvts.getRawParameterValue(parameterIDs[kLowBandGain])->load();
    settings.lowMidGainDecibels = apvts.getRawParameterValue(parameterIDs[kLowMidBandGain])->load();
    settings.hiMidGainDecibels = apvts.getRawParameterValue(parameterIDs[kHighMidBandGain])->load();
    settings.hiGainDecibels = apvts.getRawParameterValue(parameterIDs[kHighBandGain])->load();
    settings.lowQ = apvts.getRawParameterValue(parameterIDs[kLowBandQ])->load();
    settings.lowMidQ = apvts.getRawParameterValue(parameterIDs[kLowMidBandQ])->load();
    settings.hiMidQ = apvts.getRawParameterValue(parameterIDs[kHighMidBandQ])->load();
    settings.hiQ = apvts.getRawParameterValue(parameterIDs[kHighBandQ])->load();
    settings.lowFreq = apvts.getRawParameterValue(parameterIDs[kLowBandCutoff])->load();
    settings.lowMidFreq = apvts.getRawParameterValue(parameterIDs[kLowMidBandFreq])->load();
    settings.hiMidFreq = apvts.getRawParameterValue(parameterIDs[kHighMidBandFreq])->load();
    settings.hiFreq = apvts.getRawParameterValue(parameterIDs[kHighBandCutoff])->load();
    
    return settings;
};

