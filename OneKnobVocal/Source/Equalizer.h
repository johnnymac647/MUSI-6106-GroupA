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
    }

    Equalizer(juce::AudioProcessorValueTreeState* mainApvts)
    {
        ptr_apvts = mainApvts;
        gain.setGainDecibels(ptr_apvts->getRawParameterValue("EQ_POST_GAIN")->load());
    }

    void prepareToPlay(double sampleRate, int samplesPerBlock) override
    {
        juce::dsp::ProcessSpec spec{ sampleRate, static_cast<juce::uint32> (samplesPerBlock), 2 };
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