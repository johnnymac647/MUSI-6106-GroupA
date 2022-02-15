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
        gain.setGainDecibels(apvts.getRawParameterValue("GAIN")->load());
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
        
        float k = 1.f; //gain multiplier, amplify the input sample before applying it to the funciton.
        
        float tanh_k = tanh(k); //k applies in the denominators for normalization, optional
        float atan_k = atan(k);
        
        for (int channel = 0; channel < totalNumInputChannels; ++channel)
        {
            float* channelData = buffer.getWritePointer (channel);
            const int numSamplesToRender = buffer.getNumSamples();
            
            
            for(int i = 0; i < numSamplesToRender; i++){
                
                
                //Hyperbolic Tangent TANH
                channelData[i] = tanh(k * channelData[i]) / tanh_k;
                
                //Arctangent ATAN
                //channelData[i] = atan(k * channelData[i]) / atan_k;
            }
        }
        
        
        
        
        
        
        gain.setGainDecibels(apvts.getRawParameterValue("GAIN")->load());
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
        params.push_back(std::make_unique<juce::AudioParameterFloat>("GAIN", "Gain", -96.0f, 12.0f, 0.0f));
        return { params.begin() , params.end() };
    }
    juce::dsp::Gain<float> gain;
};
