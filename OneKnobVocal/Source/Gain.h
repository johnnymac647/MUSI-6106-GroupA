/*
  ==============================================================================

    Gain.h
    Created: 2 Feb 2022 11:38:12pm
    Author:  yinsile

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "ProcessorBase.h"
#include "ModdedNormalisableRange.h"

class Gain : public ProcessorBase
{
public:
    Gain():
        apvts{*this, nullptr, "Parameters", createParameterLayout()}
    {
        gain.setGainDecibels(apvts.getRawParameterValue("GAIN")->load());
        //gain.setGainDecibels(-6.0f);
    }

    void prepareToPlay(double sampleRate, int samplesPerBlock) override
    {
        juce::dsp::ProcessSpec spec{ sampleRate, static_cast<juce::uint32> (samplesPerBlock), 2 };
        gain.prepare(spec);
    }

    void processBlock(juce::AudioSampleBuffer& buffer, juce::MidiBuffer&) override
    {
        gain.setGainDecibels(apvts.getRawParameterValue("GAIN")->load());
        juce::dsp::AudioBlock<float> block(buffer);
        juce::dsp::ProcessContextReplacing<float> context(block);
        gain.process(context);
    }

    void reset() override
    {
        gain.reset();
    }

    const juce::String getName() const override { return "Gain"; }

    juce::AudioProcessorValueTreeState apvts;

private:
    juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout()
    {
        std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;
        params.push_back(std::make_unique<juce::AudioParameterFloat>("GAIN", "Gain", -96.0f, 12.0f, 0.0f));
        return { params.begin() , params.end() };
    }
    juce::dsp::Gain<float> gain;
};
