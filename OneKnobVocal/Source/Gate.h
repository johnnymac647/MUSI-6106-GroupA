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
        {-36.0f, 12.0f, 0.0f},
        {-60.0f, 0.0f, -58.0f},
        {0.0f, 50.0f, 1.0f},
        {0.0f, 100.0f, 100.0f},
        {1.0f, 10.0f, 10.0f}
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

    static void addToKnobMap(juce::HashMap<juce::String, ModdedNormalisableRange<double>>& knobValueMap)
    {
        for (int i = 0; i < effectParameters::kNumOfParameters; i++)
        {
            knobValueMap.set(parameterIDs[i],
                ModdedNormalisableRange<double>(parameterSettings[i][parameterRange::kParameterDefault],
                    parameterSettings[i][parameterRange::kParameterDefault]));
        }
    }

    Gate(juce::AudioProcessorValueTreeState* mainApvts)
    {
        ptr_apvts = mainApvts;
        gain.setGainDecibels(ptr_apvts->getRawParameterValue(parameterIDs[kPostGain])->load());
    }

    void prepareToPlay(double sampleRate, int samplesPerBlock) override
    {
        juce::dsp::ProcessSpec spec{ sampleRate, static_cast<juce::uint32> (samplesPerBlock), 2 };
        gain.prepare(spec);
        noiseGate.prepare(spec);
    }

    void processBlock(juce::AudioSampleBuffer& buffer, juce::MidiBuffer&) override
    {
        gain.setGainDecibels(ptr_apvts->getRawParameterValue(parameterIDs[kPostGain])->load());
        
        noiseGate.setAttack(ptr_apvts->getRawParameterValue(parameterIDs[kAttack])->load());
        noiseGate.setRelease(ptr_apvts->getRawParameterValue(parameterIDs[kRelease])->load());
        noiseGate.setThreshold(ptr_apvts->getRawParameterValue(parameterIDs[kThreshold])->load());
        noiseGate.setRatio(ptr_apvts->getRawParameterValue(parameterIDs[kRatio])->load());
        
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
