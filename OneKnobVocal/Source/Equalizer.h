/*
  ==============================================================================

    Equalizer.h
    Created: 2 Feb 2022 11:38:40pm
    Author:  yinsile

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "ProcessorBase.h"

class Equalizer : public ProcessorBase
{
public:
    
    //graphic EQ outline
    
    juce::dsp::IIR::Coefficients<float>* newCoefficients;
    
    //param EQ outline
    //need an array/list of filters
    //each filter needs: index, type(low/high pass/shelf, notch, etc)

    
    
    Equalizer() :
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
        juce::dsp::AudioBlock<float> block(buffer);
        juce::dsp::ProcessContextReplacing<float> context(block);
        gain.process(context);
    }

    void reset() override
    {
        gain.reset();
    }

    const juce::String getName() const override { return "Equalizer"; }

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

//make this a derived class from one of the JUCE filters???
class mVocalFilter {
public:
    enum eFilterType {
        lowPass,
        hiPass,
        lowShelf,
        hiShelf,
        bandPass,
        notch,
        peak,
        numOfFilters
    };
    
    mVocalFilter::eFilterType mFilterType;
    float m_fQ;
    float m_fFrequency;
    float m_fGain;
    
private:
};
