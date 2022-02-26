/*
  ==============================================================================

    Gate.h
    Created: 2 Feb 2022 11:38:20pm
    Author:  yinsile

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "ProcessorBase.h"

class Gate : public ProcessorBase
{
public:
    Gate() :
        apvts{ *this, nullptr, "Parameters", createParameterLayout() }
    {
        gain.setGainDecibels(apvts.getRawParameterValue("GAIN")->load());
    }

    void prepareToPlay(double sampleRate, int samplesPerBlock) override
    {
        juce::dsp::ProcessSpec spec{ sampleRate, static_cast<juce::uint32> (samplesPerBlock), 2 };
        gain.prepare(spec);
        noiseGate.prepare(spec);
    }

    void processBlock(juce::AudioSampleBuffer& buffer, juce::MidiBuffer&) override
    {

        // for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        //     buffer.clear (i, 0, buffer.getNumSamples());
        
        gain.setGainDecibels(apvts.getRawParameterValue("GAIN")->load());
        
        noiseGate.setAttack(apvts.getRawParameterValue("ATTACK")->load());
        noiseGate.setRelease(apvts.getRawParameterValue("RELEASE")->load());
        noiseGate.setThreshold(apvts.getRawParameterValue("THRESHOLD")->load());
        noiseGate.setRatio(apvts.getRawParameterValue("RATIO")->load());
        
        auto block = juce::dsp::AudioBlock<float>(buffer);
        auto context = juce::dsp::ProcessContextReplacing<float>(block);
        
        gain.process(context);
        noiseGate.process(context);

    }

    void reset() override
    {
        gain.reset();
        noiseGate.reset();
    }

    const juce::String getName() const override { return "Gate"; }

    juce::AudioProcessorValueTreeState apvts;

private:
    juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout()
    {
        std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;
        params.push_back(std::make_unique<juce::AudioParameterFloat>("GAIN", "Gain", -96.0f, 12.0f, 0.0f));
        params.push_back(std::make_unique<juce::AudioParameterFloat>("THRESHOLD", "Threshold", -60.0f, 0.0f, -18.0f));            
        params.push_back(std::make_unique<juce::AudioParameterFloat>("ATTACK", "Attack", 0.0f, 1000.0f, 1.0f));
        params.push_back(std::make_unique<juce::AudioParameterFloat>("RELEASE", "Release", 0.0f, 5000.0f, 100.0f));
        params.push_back(std::make_unique<juce::AudioParameterFloat>("RATIO", "Ratio", 1.0f, 100.0f, 10.0f));
        return { params.begin() , params.end() };
    }
    juce::dsp::Gain<float> gain;
    juce::dsp::NoiseGate<float> noiseGate;

};
