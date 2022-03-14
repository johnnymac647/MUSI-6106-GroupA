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
    static void addToParameterLayout(std::vector<std::unique_ptr<juce::RangedAudioParameter>>& params)
    {
        params.push_back(std::make_unique<juce::AudioParameterFloat>("GATE_POST_GAIN", "GatePostGain", -96.0f, 12.0f, 0.0f));
        params.push_back(std::make_unique<juce::AudioParameterFloat>("GATE_THRESHOLD", "GateThreshold", -60.0f, 0.0f, -18.0f));
        params.push_back(std::make_unique<juce::AudioParameterFloat>("GATE_ATTACK", "GateAttack", 0.0f, 1000.0f, 1.0f));
        params.push_back(std::make_unique<juce::AudioParameterFloat>("GATE_RELEASE", "GateRelease", 0.0f, 5000.0f, 100.0f));
        params.push_back(std::make_unique<juce::AudioParameterFloat>("GATE_RATIO", "GateRatio", 1.0f, 100.0f, 10.0f));
    }

    Gate(juce::AudioProcessorValueTreeState* mainApvts)
    {
        ptr_apvts = mainApvts;
        gain.setGainDecibels(ptr_apvts->getRawParameterValue("GATE_POST_GAIN")->load());
    }

    void prepareToPlay(double sampleRate, int samplesPerBlock) override
    {
        juce::dsp::ProcessSpec spec{ sampleRate, static_cast<juce::uint32> (samplesPerBlock), 2 };
        gain.prepare(spec);
        noiseGate.prepare(spec);
    }

    void processBlock(juce::AudioSampleBuffer& buffer, juce::MidiBuffer&) override
    {
        gain.setGainDecibels(ptr_apvts->getRawParameterValue("GATE_POST_GAIN")->load());
        
        noiseGate.setAttack(ptr_apvts->getRawParameterValue("GATE_ATTACK")->load());
        noiseGate.setRelease(ptr_apvts->getRawParameterValue("GATE_RELEASE")->load());
        noiseGate.setThreshold(ptr_apvts->getRawParameterValue("GATE_THRESHOLD")->load());
        noiseGate.setRatio(ptr_apvts->getRawParameterValue("GATE_RATIO")->load());
        
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

    juce::AudioProcessorValueTreeState* ptr_apvts;

private:
    juce::dsp::Gain<float> gain;
    juce::dsp::NoiseGate<float> noiseGate;

};
