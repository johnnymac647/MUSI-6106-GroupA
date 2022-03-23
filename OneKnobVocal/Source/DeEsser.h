/*
  ==============================================================================

    DeEsser.h
    Created: 2 Feb 2022 11:38:30pm
    Author:  yinsile

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "ProcessorBase.h"
#include "ModdedNormalisableRange.h"

class Deesser : public ProcessorBase
{
public:
    static void addToParameterLayout(std::vector<std::unique_ptr<juce::RangedAudioParameter>>& params)
    {
        params.push_back(std::make_unique<juce::AudioParameterFloat>("DEESSER_POST_GAIN", "DeesserPostGain", -96.0f, 12.0f, 0.0f));
        params.push_back(std::make_unique<juce::AudioParameterFloat>("DEESSER_THRESHOLD", "DeesserThreshold", -60.0f, 0.0f, -18.0f));
        params.push_back(std::make_unique<juce::AudioParameterFloat>("DEESSER_ATTACK", "DeesserAttack", 0.0f, 1000.0f, 1.0f));
        params.push_back(std::make_unique<juce::AudioParameterFloat>("DEESSER_RELEASE", "DeesserRelease", 0.0f, 5000.0f, 100.0f));
        params.push_back(std::make_unique<juce::AudioParameterFloat>("DEESSER_RATIO", "DeesserRatio", 1.0f, 100.0f, 10.0f));
        params.push_back(std::make_unique<juce::AudioParameterFloat>("DEESSER_CROSSOVERFREQ", "DeesserCrossoverFreq", 20.0f, 20000.0f, 5000.0f));
    }

    static void addToKnobMap(juce::HashMap<juce::String, ModdedNormalisableRange<float>>& knobValueMap)
    {
        knobValueMap.set("DEESSER_POST_GAIN", ModdedNormalisableRange<float>(0.0f, 0.01f));
        knobValueMap.set("DEESSER_THRESHOLD", ModdedNormalisableRange<float>(-18.0f, -17.99f));
        knobValueMap.set("DEESSER_ATTACK", ModdedNormalisableRange<float>(1.0f, 1.01f));
        knobValueMap.set("DEESSER_RELEASE", ModdedNormalisableRange<float>(10.0f, 10.01f));
        knobValueMap.set("DEESSER_RATIO", ModdedNormalisableRange<float>(1.0f, 1.01f));
        knobValueMap.set("DEESSER_CROSSOVERFREQ", ModdedNormalisableRange<float>(5000.0f, 5000.01f));
    }

    Deesser(juce::AudioProcessorValueTreeState* mainApvts)
    {
        ptr_apvts = mainApvts;
        gain.setGainDecibels(ptr_apvts->getRawParameterValue("DEESSER_POST_GAIN")->load());
    }

    void prepareToPlay(double sampleRate, int samplesPerBlock) override
    {
        juce::dsp::ProcessSpec spec{ sampleRate, static_cast<juce::uint32> (samplesPerBlock), 2 };
        gain.prepare(spec);
    
        compressor.prepare(spec);
        lowPass.prepare(spec);
        highPass.prepare(spec);
    
        lowBuffer.setSize(spec.numChannels, samplesPerBlock);
        highBuffer.setSize(spec.numChannels, samplesPerBlock);
    }

    void processBlock(juce::AudioSampleBuffer& buffer, juce::MidiBuffer&) override
    {
        auto totalNumOutputChannels = getTotalNumOutputChannels();

        lowBuffer.makeCopyOf(buffer, true);
        highBuffer.makeCopyOf(buffer, true);

        // for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        //     buffer.clear (i, 0, buffer.getNumSamples());
        
        gain.setGainDecibels(ptr_apvts->getRawParameterValue("DEESSER_POST_GAIN")->load());
        
        lowPass.setType(juce::dsp::LinkwitzRileyFilterType::lowpass);
        lowPass.setCutoffFrequency(ptr_apvts->getRawParameterValue("DEESSER_CROSSOVERFREQ")->load());
        highPass.setType(juce::dsp::LinkwitzRileyFilterType::highpass);
        highPass.setCutoffFrequency(ptr_apvts->getRawParameterValue("DEESSER_CROSSOVERFREQ")->load());

        compressor.setAttack(ptr_apvts->getRawParameterValue("DEESSER_ATTACK")->load());
        compressor.setRelease(ptr_apvts->getRawParameterValue("DEESSER_RELEASE")->load());
        compressor.setThreshold(ptr_apvts->getRawParameterValue("DEESSER_THRESHOLD")->load());
        compressor.setRatio(ptr_apvts->getRawParameterValue("DEESSER_RATIO")->load());
            
        auto lowBlock = juce::dsp::AudioBlock<float>(lowBuffer);
        auto lowContext = juce::dsp::ProcessContextReplacing<float>(lowBlock);

        auto highBlock = juce::dsp::AudioBlock<float>(highBuffer);
        auto highContext = juce::dsp::ProcessContextReplacing<float>(highBlock);
            
        // Narrow-band De-esser implementation:
        lowPass.process(lowContext);
        gain.process(lowContext);

        highPass.process(highContext);
        gain.process(highContext);
        compressor.process(highContext);

        // Sum the low and high context together
        for (int ch = 0; ch < totalNumOutputChannels; ch++)
        {
            // if listen set, output high only, else sum low and high
            buffer.copyFrom(ch, 0, lowBuffer.getReadPointer(ch), lowBuffer.getNumSamples());
            // if (!pListen->get())
            // {
            buffer.addFrom(ch, 0, highBuffer.getReadPointer(ch), highBuffer.getNumSamples());
            // }
        }

        
    }

    void reset() override
    {
        gain.reset();
        compressor.reset();
        lowPass.reset();
        highPass.reset();
    }

    const juce::String getName() const override { return "Deesser"; }

    juce::AudioProcessorValueTreeState* ptr_apvts;

private:
    juce::dsp::Gain<float> gain;

    juce::AudioBuffer<float> lowBuffer, highBuffer;
    juce::dsp::LinkwitzRileyFilter<float> lowPass, highPass;
    juce::dsp::Compressor<float> compressor;
};
