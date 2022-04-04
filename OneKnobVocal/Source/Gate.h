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
#include "ModdedNormalisableRange.h"

class Gate : public ProcessorBase
{
public:

    enum effectParameters
    {
        kPostGain = 0,
        kThreshold,
        kAttack,
        kRelease,
        kRatio,
        kNumOfParameters
    };

    inline static const juce::String parameterIDs[effectParameters::kNumOfParameters]
    {
    "GATE_POST_GAIN",
    "GATE_THRESHOLD",
    "GATE_ATTACK",
    "GATE_RELEASE",
    "GATE_RATIO"
    };

    inline static const juce::String parameterNames[effectParameters::kNumOfParameters]
    {
    "Post Gain",
    "Threshold",
    "Attack",
    "Release",
    "Ratio"
    };

    inline static const float parameterSettings[effectParameters::kNumOfParameters][parameterRange::kParameterRangeNumbers]
    {
        {-96.0f, 12.0f, 0.0f},
        {-60.0f, 0.0f, -18.0f},
        {0.0f, 1000.0f, 1.0f},
        {0.0f, 5000.0f, 100.0f},
        {1.0f, 100.0f, 10.0f}
    };

    static void addToParameterLayout(std::vector<std::unique_ptr<juce::RangedAudioParameter>>& params)
    {
        for (int i = 0; i < effectParameters::kNumOfParameters; i++)
        {
            params.push_back(std::make_unique<juce::AudioParameterFloat>(parameterIDs[i],
                "Gate " + parameterNames[i], 
                parameterSettings[i][parameterRange::kParameterStart], 
                parameterSettings[i][parameterRange::kParameterEnd],
                parameterSettings[i][parameterRange::kParameterDefault]));
        }
    }

    static void addToKnobMap(juce::HashMap<juce::String, ModdedNormalisableRange<float>>& knobValueMap)
    {
        for (int i = 0; i < effectParameters::kNumOfParameters; i++)
        {
            knobValueMap.set(parameterIDs[i],
                ModdedNormalisableRange<float>(parameterSettings[i][parameterRange::kParameterDefault],
                    parameterSettings[i][parameterRange::kParameterDefault]));
        }
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
        
        //calculate the RMS of the block size.
        //The time resolution depends on the block size of the host, but it's acceptable.
        rmsLevelLeft = juce::Decibels::gainToDecibels(buffer.getRMSLevel(0, 0, buffer.getNumSamples()));
        rmsLevelRight = juce::Decibels::gainToDecibels(buffer.getRMSLevel(1, 0, buffer.getNumSamples()));
        
        
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
    
    float rmsLevelLeft, rmsLevelRight;

};
