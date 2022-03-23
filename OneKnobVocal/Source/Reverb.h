/*
  ==============================================================================

    Reverb.h
    Created: 2 Feb 2022 11:39:18pm
    Author:  yinsile

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "ProcessorBase.h"

class Reverb : public ProcessorBase
{
public:
    static void addToParameterLayout(std::vector<std::unique_ptr<juce::RangedAudioParameter>>& params)
    {
        params.push_back(std::make_unique<juce::AudioParameterFloat>("REVERB_POST_GAIN", "ReverbPostGain", -96.0f, 12.0f, 0.0f));
        params.push_back(std::make_unique<juce::AudioParameterFloat>("REVERB_ROOM_SIZE", "ReverbRoomSize", 0.f, 1.f, 0.5f));
        params.push_back(std::make_unique<juce::AudioParameterFloat>("REVERB_DAMPING", "ReverbDamping", 0.f, 1.f, 0.5f));
        params.push_back(std::make_unique<juce::AudioParameterFloat>("REVERB_WET_LEVEL", "ReverbWetLevel", -96.0f, 12.0f, -96.0f));
        params.push_back(std::make_unique<juce::AudioParameterFloat>("REVERB_DRY_LEVEL", "ReverbDryLevel", -96.0f, 12.0f, 0.0f));
        params.push_back(std::make_unique<juce::AudioParameterFloat>("REVERB_WIDTH", "ReverbWidth", 0.f, 1.f, 0.5f));
    }

    static void addToKnobMap(juce::HashMap<juce::String, juce::NormalisableRange<float>>& knobValueMap)
    {
        knobValueMap.set("REVERB_POST_GAIN", juce::NormalisableRange<float>(0.0f, 0.01f));
        knobValueMap.set("REVERB_ROOM_SIZE", juce::NormalisableRange<float>(0.5f, 0.51f));
        knobValueMap.set("REVERB_DAMPING", juce::NormalisableRange<float>(0.5f, 0.51f));
        knobValueMap.set("REVERB_WET_LEVEL", juce::NormalisableRange<float>(-96.0f, -95.99f));
        knobValueMap.set("REVERB_DRY_LEVEL", juce::NormalisableRange<float>(0.0f, 0.01f));
        knobValueMap.set("REVERB_WIDTH", juce::NormalisableRange<float>(0.5f, 0.51f));
    }

    Reverb(juce::AudioProcessorValueTreeState* mainApvts)
    {
        ptr_apvts = mainApvts;
    }

    void prepareToPlay(double sampleRate, int samplesPerBlock) override
    {
        juce::dsp::ProcessSpec spec{ sampleRate, static_cast<juce::uint32> (samplesPerBlock), 2 };
        reverb.prepare(spec);
        gain.prepare(spec);
        gain.setGainDecibels(ptr_apvts->getRawParameterValue("REVERB_POST_GAIN")->load());
        getReverbParameters(*ptr_apvts);
    }

    void processBlock(juce::AudioSampleBuffer& buffer, juce::MidiBuffer&) override
    {
        gain.setGainDecibels(ptr_apvts->getRawParameterValue("REVERB_POST_GAIN")->load());
        getReverbParameters(*ptr_apvts);
        juce::dsp::AudioBlock<float> block(buffer);
        juce::dsp::ProcessContextReplacing<float> context(block);
        reverb.process(context);
        gain.process(context);
    }

    void reset() override
    {
        gain.reset();
    }

    const juce::String getName() const override { return "Reverb"; }

    juce::AudioProcessorValueTreeState* ptr_apvts;

private:
    void getReverbParameters(const juce::AudioProcessorValueTreeState &apvts);
    juce::dsp::Reverb reverb;
    juce::dsp::Gain<float> gain;
};