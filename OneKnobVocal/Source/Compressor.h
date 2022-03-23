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
    static void addToParameterLayout(std::vector<std::unique_ptr<juce::RangedAudioParameter>>& params)
    {
        params.push_back(std::make_unique<juce::AudioParameterFloat>("COMPRESSOR_PRE_GAIN", "CompressorPreGain", -96.0f, 12.0f, 0.0f));
        params.push_back(std::make_unique<juce::AudioParameterFloat>("COMPRESSOR_POST_GAIN", "CompressorPostGain", -96.0f, 12.0f, 0.0f));
        params.push_back(std::make_unique<juce::AudioParameterFloat>("COMPRESSOR_MAKEUP_GAIN", "CompressorMakeupGain", -96.0f, 12.0f, 0.0f));
        params.push_back(std::make_unique<juce::AudioParameterFloat>("COMPRESSOR_ATTACK", "CompressorAttack", 0.0f, 1000.0f, 1.0f));
        params.push_back(std::make_unique<juce::AudioParameterFloat>("COMPRESSOR_RELEASE", "CompressorRelease", 0.0f, 5000.0f, 10.0f));
        params.push_back(std::make_unique<juce::AudioParameterFloat>("COMPRESSOR_THRESHOLD", "CompressorThreshold", -60.0f, 0.0f, -18.0f));
        params.push_back(std::make_unique<juce::AudioParameterFloat>("COMPRESSOR_RATIO", "CompressorRatio", 1.0f, 100.0f, 1.0f));
    }

    static void addToKnobMap(juce::HashMap<juce::String, juce::NormalisableRange<float>>& knobValueMap)
    {
        knobValueMap.set("COMPRESSOR_PRE_GAIN", juce::NormalisableRange<float>(-96.0f, 12.0f));
        knobValueMap.set("COMPRESSOR_POST_GAIN", juce::NormalisableRange<float>(-96.0f, 12.0f));
        knobValueMap.set("COMPRESSOR_MAKEUP_GAIN", juce::NormalisableRange<float>(-96.0f, 12.0f));
        knobValueMap.set("COMPRESSOR_ATTACK", juce::NormalisableRange<float>(0.0f, 1000.0f));
        knobValueMap.set("COMPRESSOR_RELEASE", juce::NormalisableRange<float>(0.0f, 5000.0f));
        knobValueMap.set("COMPRESSOR_THRESHOLD", juce::NormalisableRange<float>(-60.0f, 0.0f));
        knobValueMap.set("COMPRESSOR_RATIO", juce::NormalisableRange<float>(1.0f, 100.0f));
    }

    Compressor(juce::AudioProcessorValueTreeState* mainApvts)
    {
        ptr_apvts = mainApvts;
        inputGain.setGainDecibels(ptr_apvts->getRawParameterValue("COMPRESSOR_PRE_GAIN")->load());
        makeUpGain.setGainDecibels(ptr_apvts->getRawParameterValue("COMPRESSOR_MAKEUP_GAIN")->load());
        outputGain.setGainDecibels(ptr_apvts->getRawParameterValue("COMPRESSOR_POST_GAIN")->load());
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
        
        
        inputGain.setGainDecibels(ptr_apvts->getRawParameterValue("COMPRESSOR_PRE_GAIN")->load());
        makeUpGain.setGainDecibels(ptr_apvts->getRawParameterValue("COMPRESSOR_MAKEUP_GAIN")->load());
        outputGain.setGainDecibels(ptr_apvts->getRawParameterValue("COMPRESSOR_POST_GAIN")->load());
        
        compressor.setAttack(ptr_apvts->getRawParameterValue("COMPRESSOR_ATTACK")->load());
        compressor.setRelease(ptr_apvts->getRawParameterValue("COMPRESSOR_RELEASE")->load());
        compressor.setThreshold(ptr_apvts->getRawParameterValue("COMPRESSOR_THRESHOLD")->load());
        compressor.setRatio(ptr_apvts->getRawParameterValue("COMPRESSOR_RATIO")->load());
        
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

    juce::AudioProcessorValueTreeState* ptr_apvts;

private:
    
    juce::dsp::Compressor<float> compressor;
    juce::dsp::Gain<float> inputGain;
    juce::dsp::Gain<float> outputGain ;
    juce::dsp::Gain<float> makeUpGain ;
};
