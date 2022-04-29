/*
  ==============================================================================

    Equalizer.cpp
    Created: 2 Feb 2022 11:38:40pm
    Author:  yinsile

  ==============================================================================
*/

#include "Equalizer.h"

EQSettings getEQSettings(juce::AudioProcessorValueTreeState& apvts){
    EQSettings settings;
    
    settings.postGainDecibels = apvts.getRawParameterValue(Equalizer::parameterIDs[Equalizer::kPostGain])->load();
    settings.lowGainDecibels = apvts.getRawParameterValue(Equalizer::parameterIDs[Equalizer::kLowBandGain])->load();
    settings.lowMidGainDecibels = apvts.getRawParameterValue(Equalizer::parameterIDs[Equalizer::kLowMidBandGain])->load();
    settings.hiMidGainDecibels = apvts.getRawParameterValue(Equalizer::parameterIDs[Equalizer::kHighMidBandGain])->load();
    settings.hiGainDecibels = apvts.getRawParameterValue(Equalizer::parameterIDs[Equalizer::kHighBandGain])->load();
    settings.lowQ = apvts.getRawParameterValue(Equalizer::parameterIDs[Equalizer::kLowBandQ])->load();
    settings.lowMidQ = apvts.getRawParameterValue(Equalizer::parameterIDs[Equalizer::kLowMidBandQ])->load();
    settings.hiMidQ = apvts.getRawParameterValue(Equalizer::parameterIDs[Equalizer::kHighMidBandQ])->load();
    settings.hiQ = apvts.getRawParameterValue(Equalizer::parameterIDs[Equalizer::kHighBandQ])->load();
    settings.lowFreq = apvts.getRawParameterValue(Equalizer::parameterIDs[Equalizer::kLowBandCutoff])->load();
    settings.lowMidFreq = apvts.getRawParameterValue(Equalizer::parameterIDs[Equalizer::kLowMidBandFreq])->load();
    settings.hiMidFreq = apvts.getRawParameterValue(Equalizer::parameterIDs[Equalizer::kHighMidBandFreq])->load();
    settings.hiFreq = apvts.getRawParameterValue(Equalizer::parameterIDs[Equalizer::kHighBandCutoff])->load();
    
    return settings;
};

