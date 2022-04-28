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
#include "ModdedNormalisableRange.h"

class Saturator : public ProcessorBase
{
public:

    enum effectParameters
    {
        kPostGain = 0,
        kMix,
        kPreGain,
        kNumOfParameters
    };

    inline static const juce::String parameterIDs[effectParameters::kNumOfParameters]
    {
        "SATURATOR_POST_GAIN",
        "SATURATOR_MIX",
        "SATURATOR_PRE_GAIN"
    };

    inline static const juce::String parameterNames[effectParameters::kNumOfParameters]
    {
        "Post Gain",
        "Mix",
        "Pre Gain"
    };

    inline static const float parameterSettings[effectParameters::kNumOfParameters][parameterRange::kParameterRangeNumbers]
    {
        {-96.0f, 12.0f, 0.0f},
        {0.0f, 1.0f, 0.0f},
        {0.01f, 10.0f, 1.0f}
    };

    static void addToParameterLayout(std::vector<std::unique_ptr<juce::RangedAudioParameter>>& params)
    {
        for (int i = 0; i < effectParameters::kNumOfParameters; i++)
        {
            params.push_back(std::make_unique<juce::AudioParameterFloat>(parameterIDs[i],
                "Saturator " + parameterNames[i],
                parameterSettings[i][parameterRange::kParameterStart],
                parameterSettings[i][parameterRange::kParameterEnd],
                parameterSettings[i][parameterRange::kParameterDefault]));
        }
    }

    static void addToKnobMap(juce::HashMap<juce::String, ModdedNormalisableRange<double>>& knobValueMap)
    {
        for (int i = 0; i < effectParameters::kNumOfParameters; i++)
        {
            knobValueMap.set(parameterIDs[i],
                ModdedNormalisableRange<double>(parameterSettings[i][parameterRange::kParameterDefault],
                    parameterSettings[i][parameterRange::kParameterDefault]));
        }
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
