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
    Saturator() :
        apvts{ *this, nullptr, "Parameters", createParameterLayout() }
    {
        gain.setGainDecibels(apvts.getRawParameterValue("OUTPUT")->load());
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
        float k = (apvts.getRawParameterValue("GAIN")->load());
        
        
        //k applies in the denominators for normalization, optional
        //float tanh_k = tanh(k);
        float atan_k = atan(k);
        
        
        float mix = (apvts.getRawParameterValue("MIX")->load());
        
        
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
        
        gain.setGainDecibels(apvts.getRawParameterValue("OUTPUT")->load());
        juce::dsp::AudioBlock<float> block(buffer);
        juce::dsp::ProcessContextReplacing<float> context(block);
        gain.process(context);
        
    }

    void reset() override
    {
        gain.reset();
    }

    const juce::String getName() const override { return "Saturator"; }

    juce::AudioProcessorValueTreeState apvts;

private:
    juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout()
    {
        std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;
        params.push_back(std::make_unique<juce::AudioParameterFloat>("GAIN", "Gain", 0.01f, 10.0f, 1.0f));
        params.push_back(std::make_unique<juce::AudioParameterFloat>("MIX", "Mix", 0.0f, 1.0f, 1.0f));
        params.push_back(std::make_unique<juce::AudioParameterFloat>("OUTPUT", "Output", -96.0f, 12.0f, 0.0f));
        
        return { params.begin() , params.end() };
    }
    juce::dsp::Gain<float> gain;
};
