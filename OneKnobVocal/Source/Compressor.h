/*
  ==============================================================================

    Compressor.h
    Created: 2 Feb 2022 11:38:53pm
    Author:  yinsile

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "ProcessorBase.h"

class Compressor : public ProcessorBase
{
public:
    Compressor() :
        apvts{ *this, nullptr, "Parameters", createParameterLayout() }
    {
        inputGain.setGainDecibels(apvts.getRawParameterValue("INPUTGAIN")->load());
        makeUpGain.setGainDecibels(apvts.getRawParameterValue("MAKEUPGAIN")->load());
        outputGain.setGainDecibels(apvts.getRawParameterValue("OUTPUTGAIN")->load());
        
    }

    void prepareToPlay(double sampleRate, int samplesPerBlock) override
    {
        juce::dsp::ProcessSpec spec{ sampleRate, static_cast<juce::uint32> (samplesPerBlock), 2 };
        
        compressor.prepare(spec);
        inputGain.prepare(spec);
        outputGain.prepare(spec);
        makeUpGain.prepare(spec);
    }

    void processBlock(juce::AudioSampleBuffer& buffer, juce::MidiBuffer&) override
    {
        
        
        inputGain.setGainDecibels(apvts.getRawParameterValue("INPUTGAIN")->load());
        outputGain.setGainDecibels(apvts.getRawParameterValue("OUTPUTGAIN")->load());
        makeUpGain.setGainDecibels(apvts.getRawParameterValue("MAKEUPGAIN")->load());
        
        compressor.setAttack(apvts.getRawParameterValue("ATTACK")->load());
        compressor.setRelease(apvts.getRawParameterValue("RELEASE")->load());
        compressor.setThreshold(apvts.getRawParameterValue("THRESHOLD")->load());
        compressor.setRatio(apvts.getRawParameterValue("RATIO")->load());
        
        juce::dsp::AudioBlock<float> block(buffer);
        juce::dsp::ProcessContextReplacing<float> context(block);
        
        inputGain.process(context);
        compressor.process(context);
        makeUpGain.process(context);
        outputGain.process(context);
    }

    void reset() override
    {
        inputGain.reset();
        makeUpGain.reset();
        outputGain.reset();
        compressor.reset();
    }

    const juce::String getName() const override { return "Compressor"; }

    juce::AudioProcessorValueTreeState apvts;

private:
    juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout()
    {
        std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;
        params.push_back(std::make_unique<juce::AudioParameterFloat>("INPUTGAIN", "InputGain", -96.0f, 12.0f, 0.0f));
        params.push_back(std::make_unique<juce::AudioParameterFloat>("OUTPUTGAIN", "OutputGain", -96.0f, 12.0f, 0.0f));
        params.push_back(std::make_unique<juce::AudioParameterFloat>("MAKEUPGAIN", "MakeupGain", -96.0f, 12.0f, 0.0f));
        params.push_back(std::make_unique<juce::AudioParameterFloat>("ATTACK", "Attack", 0.0f, 1000.0f, 1.0f));
        params.push_back(std::make_unique<juce::AudioParameterFloat>("RELEASE", "Release", 0.0f, 5000.0f, 10.0f));
        params.push_back(std::make_unique<juce::AudioParameterFloat>("THRESHOLD", "Threshold", -60.0f, 0.0f, -18.0f));
        params.push_back(std::make_unique<juce::AudioParameterFloat>("RATIO", "Ratio", 1.0f, 100.0f, 1.0f));
        
        return { params.begin() , params.end() };
    }
    juce::dsp::Compressor<float> compressor;
    juce::dsp::Gain<float> inputGain;
    juce::dsp::Gain<float> outputGain ;
    juce::dsp::Gain<float> makeUpGain ;
};
