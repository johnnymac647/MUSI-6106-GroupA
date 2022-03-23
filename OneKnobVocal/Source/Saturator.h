/*
  ==============================================================================

    Saturator.h
    Created: 2 Feb 2022 11:39:01pm
    Author:  yinsile

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include <math.h>
#include "ProcessorBase.h"

class Saturator : public ProcessorBase
{
public:
    static void addToParameterLayout(std::vector<std::unique_ptr<juce::RangedAudioParameter>>& params)
    {
        params.push_back(std::make_unique<juce::AudioParameterFloat>("SATURATOR_PRE_GAIN", "SaturatorPreGain", 0.01f, 10.0f, 1.0f));
        params.push_back(std::make_unique<juce::AudioParameterFloat>("SATURATOR_MIX", "SaturatorMix", 0.0f, 1.0f, 0.0f));
        params.push_back(std::make_unique<juce::AudioParameterFloat>("SATURATOR_POST_GAIN", "SaturatorPostGain", -96.0f, 12.0f, 0.0f));
    }

    static void addToKnobMap(juce::HashMap<juce::String, juce::NormalisableRange<float>>& knobValueMap)
    {
        knobValueMap.set("SATURATOR_PRE_GAIN", juce::NormalisableRange<float>(1.0f, 1.01f));
        knobValueMap.set("SATURATOR_MIX", juce::NormalisableRange<float>(0.0f, 0.01f));
        knobValueMap.set("SATURATOR_POST_GAIN", juce::NormalisableRange<float>(0.0f, 0.01f));
    }

    Saturator(juce::AudioProcessorValueTreeState* parantApvts) 
    {
        ptr_apvts = parantApvts;
        gain.setGainDecibels(ptr_apvts->getRawParameterValue("SATURATOR_POST_GAIN")->load());
    }


    void prepareToPlay(double sampleRate, int samplesPerBlock) override
    {
        juce::dsp::ProcessSpec spec{ sampleRate, static_cast<juce::uint32> (samplesPerBlock), 2 };
        gain.prepare(spec);
    }

    void processBlock(juce::AudioSampleBuffer& buffer, juce::MidiBuffer&) override
    {
        const int totalNumInputChannels  = getTotalNumInputChannels();
        //const int totalNumOutputChannels = getTotalNumOutputChannels();
        
        /*
        Pirkle, Will. Designing Audio Effect Plug-Ins in C++: with digital audio signal processing theory. Routledge, 2012. Table 19.1
        */
        
        //gain multiplier, amplify the input sample before applying it to the funciton.
        float k = (ptr_apvts->getRawParameterValue("SATURATOR_PRE_GAIN")->load());
        
        
        //k applies in the denominators for normalization, optional
        //float tanh_k = tanh(k);
        float atan_k = atan(k);
        
        
        float mix = (ptr_apvts->getRawParameterValue("SATURATOR_MIX")->load());
        
        
        for (int channel = 0; channel < totalNumInputChannels; ++channel)
        {
            float* channelData = buffer.getWritePointer (channel);
            const int numSamplesToRender = buffer.getNumSamples();
            
            
            for(int i = 0; i < numSamplesToRender; i++){
                
                
                //Hyperbolic Tangent TANH
                //channelData[i] = (1. - mix) * channelData[i] +
                //                mix * (tanh(k * channelData[i]) / tanh_k);
                
                //Arctangent ATAN
                channelData[i] = (1. - mix) * channelData[i] +
                                mix * (atan(k * channelData[i]) / atan_k);;
            }
        }
        
        gain.setGainDecibels(ptr_apvts->getRawParameterValue("SATURATOR_POST_GAIN")->load());
        juce::dsp::AudioBlock<float> block(buffer);
        juce::dsp::ProcessContextReplacing<float> context(block);
        gain.process(context);
        
    }

    void reset() override
    {
        gain.reset();
    }

    const juce::String getName() const override { return "Saturator"; }

    juce::AudioProcessorValueTreeState* ptr_apvts;

private:
    juce::dsp::Gain<float> gain;
};
