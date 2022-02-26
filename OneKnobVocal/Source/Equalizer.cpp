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
    
    settings.postGainDecibels = apvts.getRawParameterValue("EQ_POST_GAIN")->load();
    settings.lowGainDecibels = apvts.getRawParameterValue("EQ_LOW_BAND_GAIN")->load();
    settings.lowMidGainDecibels = apvts.getRawParameterValue("EQ_LOWMID_BAND_GAIN")->load();
    settings.hiMidGainDecibels = apvts.getRawParameterValue("EQ_HIMID_BAND_GAIN")->load();
    settings.hiGainDecibels = apvts.getRawParameterValue("EQ_HI_BAND_GAIN")->load();
    settings.lowQ = apvts.getRawParameterValue("EQ_LOW_BAND_QF")->load();
    settings.lowMidQ = apvts.getRawParameterValue("EQ_LOWMID_BAND_QF")->load();
    settings.hiMidQ = apvts.getRawParameterValue("EQ_HIMID_BAND_QF")->load();
    settings.hiQ = apvts.getRawParameterValue("EQ_HI_BAND_QF")->load();
    settings.lowFreq = apvts.getRawParameterValue("EQ_LOW_BAND_CUTOFF")->load();
    settings.lowMidFreq = apvts.getRawParameterValue("EQ_LOWMID_BAND_FREQ")->load();
    settings.hiMidFreq = apvts.getRawParameterValue("EQ_HIMID_BAND_FREQ")->load();
    settings.hiFreq = apvts.getRawParameterValue("EQ_HI_BAND_CUTOFF")->load();
    
    return settings;
};

