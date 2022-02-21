/*
  ==============================================================================

    Equalizer.h
    Created: 2 Feb 2022 11:38:40pm
    Author:  yinsile

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "ProcessorBase.h"

class Equalizer : public ProcessorBase
{
public:
    static void addToParameterLayout(std::vector<std::unique_ptr<juce::RangedAudioParameter>>& params)
    {
        params.push_back(std::make_unique<juce::AudioParameterFloat>("EQ_POST_GAIN", "EqualizerPostGain", -96.0f, 12.0f, 0.0f));
        params.push_back(std::make_unique<juce::AudioParameterFloat>("EQ_LOW_BAND_GAIN", "EQLowBandGain", -24.0f, 12.0f, 0.0f));
        params.push_back(std::make_unique<juce::AudioParameterFloat>("EQ_LOW_BAND_CUTOFF", "EQLowBandCutoff", 50.0f, 200.0f, 100.0f));
        params.push_back(std::make_unique<juce::AudioParameterFloat>("EQ_LOW_BAND_QF", "EQLowBandQFactor", 0.01f, 10.0f, 0.71f));
        params.push_back(std::make_unique<juce::AudioParameterFloat>("EQ_LOWMID_BAND_GAIN", "EQLowMidBandGain", -24.0f, 12.0f, 0.0f));
        params.push_back(std::make_unique<juce::AudioParameterFloat>("EQ_LOWMID_BAND_FREQ", "EQLowMidBandFrequency", 100.0f, 2000.0f, 400.0f));
        params.push_back(std::make_unique<juce::AudioParameterFloat>("EQ_LOWMID_BAND_QF", "EQLowMidBandQFactor", 0.01f, 10.0f, 0.71f));
        params.push_back(std::make_unique<juce::AudioParameterFloat>("EQ_HIMID_BAND_GAIN", "EQHighMidBandGain", -24.0f, 12.0f, 0.0f));
        params.push_back(std::make_unique<juce::AudioParameterFloat>("EQ_HIMID_BAND_FREQ", "EQHighMidBandFrequency", 800.0f, 8000.0f, 1000.0f));
        params.push_back(std::make_unique<juce::AudioParameterFloat>("EQ_HIMID_BAND_QF", "EQHighMidBandQFactor", 0.01f, 10.0f, 0.71f));
        params.push_back(std::make_unique<juce::AudioParameterFloat>("EQ_HI_BAND_GAIN", "EQHighBandGain", -24.0f, 12.0f, 0.0f));
        params.push_back(std::make_unique<juce::AudioParameterFloat>("EQ_HI_BAND_CUTOFF", "EQHighBandCutoff", 2000.0f, 16000.0f, 8000.0f));
        params.push_back(std::make_unique<juce::AudioParameterFloat>("EQ_HI_BAND_QF", "EQHighBandQFactor", 0.01f, 10.0f, 0.71f));
    }

    Equalizer(juce::AudioProcessorValueTreeState* mainApvts)
    {
        ptr_apvts = mainApvts;
    }

    void prepareToPlay(double sampleRate, int samplesPerBlock) override
    {
        juce::dsp::ProcessSpec spec{ sampleRate, static_cast<juce::uint32> (samplesPerBlock), 2 };
        gain.setGainDecibels(ptr_apvts->getRawParameterValue("EQ_POST_GAIN")->load());
        gain.prepare(spec);
    }

    void processBlock(juce::AudioSampleBuffer& buffer, juce::MidiBuffer&) override
    {
        gain.setGainDecibels(ptr_apvts->getRawParameterValue("EQ_POST_GAIN")->load());
        juce::dsp::AudioBlock<float> block(buffer);
        juce::dsp::ProcessContextReplacing<float> context(block);
        gain.process(context);
    }

    void reset() override
    {
        gain.reset();
    }

    const juce::String getName() const override { return "Equalizer"; }

    juce::AudioProcessorValueTreeState* ptr_apvts;

private:
    juce::dsp::Gain<float> gain;

};