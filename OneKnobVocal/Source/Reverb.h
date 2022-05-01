/*
  ==============================================================================

    Reverb.h
    Created: 2 Feb 2022 11:39:18pm
    Author:  yinsile

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "ProcessorBase.h"
#include "ModdedNormalisableRange.h"

class Reverb : public ProcessorBase
{
public:

    enum effectParameters
    {
        kPostGain = 0,
        kRoomSize,
        kDamping,
        kWetLevel,
        kDryLevel,
        kWidth,
        kNumOfParameters
    };

    inline static const juce::String parameterIDs[effectParameters::kNumOfParameters]
    {
        "REVERB_POST_GAIN",
        "REVERB_ROOM_SIZE",
        "REVERB_DAMPING",
        "REVERB_WET_LEVEL",
        "REVERB_DRY_LEVEL",
        "REVERB_WIDTH"
    };

    inline static const juce::String parameterNames[effectParameters::kNumOfParameters]
    {
        "Post Gain",
        "Room Size",
        "Damping",
        "Wet Level",
        "Dry Level",
        "Width"
    };

    inline static const float parameterSettings[effectParameters::kNumOfParameters][parameterRange::kParameterRangeNumbers]
    {
        {-36.0f, 12.0f, 0.0f},
        {0.f, 1.f, 0.5f},
        {0.f, 1.f, 0.5f},
        {-96.0f, 12.0f, 0.0f},
        {-96.0f, 12.0f, 0.0f},
        {0.f, 1.f, 0.5f}
    };

    static void addToParameterLayout(std::vector<std::unique_ptr<juce::RangedAudioParameter>>& params)
    {
        for (int i = 0; i < effectParameters::kNumOfParameters; i++)
        {
            params.push_back(std::make_unique<juce::AudioParameterFloat>(parameterIDs[i],
                "Reverb " + parameterNames[i],
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

    Reverb(juce::AudioProcessorValueTreeState* mainApvts)
    {
        ptr_apvts = mainApvts;
    }

    void prepareToPlay(double sampleRate, int samplesPerBlock) override
    {
        juce::dsp::ProcessSpec spec{ sampleRate, static_cast<juce::uint32> (samplesPerBlock), 2 };
        reverb.prepare(spec);
        gain.prepare(spec);
        gain.setGainDecibels(ptr_apvts->getRawParameterValue(parameterIDs[kPostGain])->load());
        getReverbParameters(*ptr_apvts);
    }

    void processBlock(juce::AudioSampleBuffer& buffer, juce::MidiBuffer&) override
    {
        gain.setGainDecibels(ptr_apvts->getRawParameterValue(parameterIDs[kPostGain])->load());
        getReverbParameters(*ptr_apvts);
        juce::dsp::AudioBlock<float> block(buffer);
        juce::dsp::ProcessContextReplacing<float> context(block);
        reverb.process(context);
        gain.process(context);
    }

    void reset() override
    {
        gain.reset();
    }

    const juce::String getName() const override { return "Reverb"; }

    juce::AudioProcessorValueTreeState* ptr_apvts;

private:
    void getReverbParameters(const juce::AudioProcessorValueTreeState &apvts);
    juce::dsp::Reverb reverb;
    juce::dsp::Gain<float> gain;
};
