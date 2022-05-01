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
#include "ModdedNormalisableRange.h"

class Compressor : public ProcessorBase
{
public:

    enum effectParameters
    {
        kPostGain = 0,
        kPreGain,
        kThreshold,
        kAttack,
        kRelease,
        kRatio,
        kMakeupGain,
        kNumOfParameters
    };

    inline static const juce::String parameterIDs[effectParameters::kNumOfParameters]
    {
        "COMPRESSOR_POST_GAIN",
        "COMPRESSOR_PRE_GAIN",
        "COMPRESSOR_THRESHOLD",
        "COMPRESSOR_ATTACK",
        "COMPRESSOR_RELEASE",
        "COMPRESSOR_RATIO",
        "COMPRESSOR_MAKEUP_GAIN"
    };

    inline static const juce::String parameterNames[effectParameters::kNumOfParameters]
    {
        "Post Gain",
        "Pre Gain",
        "Threshold",
        "Attack",
        "Release",
        "Ratio",
        "Makeup Gain"
    };

    inline static const float parameterSettings[effectParameters::kNumOfParameters][parameterRange::kParameterRangeNumbers]
    {
        {-36.0f, 12.0f, 0.0f},
        {-36.0f, 12.0f, 0.0f},
        {-48.0f, 0.0f, -18.0f},
        {0.0f, 50.0f, 1.0f},
        {0.0f, 500.0f, 100.0f},
        {1.0f, 10.0f, 10.0f},
        {-36.0f, 12.0f, 0.0f}
    };

    static void addToParameterLayout(std::vector<std::unique_ptr<juce::RangedAudioParameter>>& params)
    {
        for (int i = 0; i < effectParameters::kNumOfParameters; i++)
        {
            params.push_back(std::make_unique<juce::AudioParameterFloat>(parameterIDs[i],
                "Compressor " + parameterNames[i],
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

    Compressor(juce::AudioProcessorValueTreeState* mainApvts)
    {
        ptr_apvts = mainApvts;
        inputGain.setGainDecibels(ptr_apvts->getRawParameterValue(parameterIDs[kPreGain])->load());
        makeUpGain.setGainDecibels(ptr_apvts->getRawParameterValue(parameterIDs[kMakeupGain])->load());
        outputGain.setGainDecibels(ptr_apvts->getRawParameterValue(parameterIDs[kPostGain])->load());
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
        
        
        inputGain.setGainDecibels(ptr_apvts->getRawParameterValue(parameterIDs[kPreGain])->load());
        makeUpGain.setGainDecibels(ptr_apvts->getRawParameterValue(parameterIDs[kMakeupGain])->load());
        outputGain.setGainDecibels(ptr_apvts->getRawParameterValue(parameterIDs[kPostGain])->load());
        
        compressor.setAttack(ptr_apvts->getRawParameterValue(parameterIDs[kAttack])->load());
        compressor.setRelease(ptr_apvts->getRawParameterValue(parameterIDs[kRelease])->load());
        compressor.setThreshold(ptr_apvts->getRawParameterValue(parameterIDs[kThreshold])->load());
        compressor.setRatio(ptr_apvts->getRawParameterValue(parameterIDs[kRatio])->load());
        
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
