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

struct EQSettings{
    float postGainDecibels{0}, lowGainDecibels{0}, lowMidGainDecibels{0}, hiMidGainDecibels{0}, hiGainDecibels{0};
    float lowQ{0}, lowMidQ{0}, hiMidQ{0}, hiQ{0};
    float lowFreq{0}, lowMidFreq{0}, hiMidFreq{0}, hiFreq{0};
    
};

EQSettings getEQSettings(juce::AudioProcessorValueTreeState& apvts);


class Equalizer : public ProcessorBase
{
public:
    static void addToParameterLayout(std::vector<std::unique_ptr<juce::RangedAudioParameter>>& params)
    {
        params.push_back(std::make_unique<juce::AudioParameterFloat>("EQ_POST_GAIN", "EqualizerPostGain", -96.0f, 12.0f, 0.0f));
        params.push_back(std::make_unique<juce::AudioParameterFloat>("EQ_LOW_BAND_GAIN", "EQLowBandGain", -24.0f, 12.0f, 0.0f));
        params.push_back(std::make_unique<juce::AudioParameterFloat>("EQ_LOW_BAND_CUTOFF", "EQLowBandCutoff", 50.0f, 200.0f, 100.0f));
        params.push_back(std::make_unique<juce::AudioParameterFloat>("EQ_LOW_BAND_QF", "EQLowBandQFactor", 0.01f, 10.0f, 0.71f));
        params.push_back(std::make_unique<juce::AudioParameterFloat>("EQ_LOWMID_BAND_GAIN", "EQLowMidBandGain", -24.0f, 12.0f, 0.0f));
        params.push_back(std::make_unique<juce::AudioParameterFloat>("EQ_LOWMID_BAND_FREQ", "EQLowMidBandFrequency", 100.0f, 2000.0f, 400.0f));
        params.push_back(std::make_unique<juce::AudioParameterFloat>("EQ_LOWMID_BAND_QF", "EQLowMidBandQFactor", 0.01f, 10.0f, 0.71f));
        params.push_back(std::make_unique<juce::AudioParameterFloat>("EQ_HIMID_BAND_GAIN", "EQHighMidBandGain", -24.0f, 12.0f, 0.0f));
        params.push_back(std::make_unique<juce::AudioParameterFloat>("EQ_HIMID_BAND_FREQ", "EQHighMidBandFrequency", 800.0f, 8000.0f, 1000.0f));
        params.push_back(std::make_unique<juce::AudioParameterFloat>("EQ_HIMID_BAND_QF", "EQHighMidBandQFactor", 0.01f, 10.0f, 0.71f));
        params.push_back(std::make_unique<juce::AudioParameterFloat>("EQ_HI_BAND_GAIN", "EQHighBandGain", -24.0f, 12.0f, 0.0f));
        params.push_back(std::make_unique<juce::AudioParameterFloat>("EQ_HI_BAND_CUTOFF", "EQHighBandCutoff", 2000.0f, 16000.0f, 8000.0f));
        params.push_back(std::make_unique<juce::AudioParameterFloat>("EQ_HI_BAND_QF", "EQHighBandQFactor", 0.01f, 10.0f, 0.71f));
    }

    Equalizer(juce::AudioProcessorValueTreeState* mainApvts)
    {
        ptr_apvts = mainApvts;
    }

    void prepareToPlay(double sampleRate, int samplesPerBlock) override
    {
//        juce::dsp::ProcessSpec spec{ sampleRate, static_cast<juce::uint32> (samplesPerBlock), 2 };
        juce::dsp::ProcessSpec spec;
        spec.maximumBlockSize = samplesPerBlock;
        spec.numChannels = 1;
        spec.sampleRate = sampleRate;
        
        leftChain.prepare(spec);
        rightChain.prepare(spec);
        
//        gain.setGainDecibels(ptr_apvts->getRawParameterValue("EQ_POST_GAIN")->load());
//        gain.prepare(spec);
        
        
        auto eqSettings = getEQSettings(*ptr_apvts);
        auto lowCoefficients = juce::dsp::IIR::Coefficients<float>::makeLowShelf(sampleRate, eqSettings.lowFreq, eqSettings.lowQ, juce::Decibels::decibelsToGain(eqSettings.lowGainDecibels));
        auto lowMidCoefficients = juce::dsp::IIR::Coefficients<float>::makePeakFilter(sampleRate, eqSettings.lowMidFreq, eqSettings.lowMidQ, juce::Decibels::decibelsToGain(eqSettings.lowMidGainDecibels));
        auto hiMidCoefficients = juce::dsp::IIR::Coefficients<float>::makePeakFilter(sampleRate, eqSettings.hiMidFreq, eqSettings.hiMidQ, juce::Decibels::decibelsToGain(eqSettings.hiMidGainDecibels));
        auto hiCoefficients = juce::dsp::IIR::Coefficients<float>::makeHighShelf(sampleRate, eqSettings.hiFreq, eqSettings.hiQ, juce::Decibels::decibelsToGain(eqSettings.hiGainDecibels));
        
//        *monoChain.get<ChainPositions::low>().coefficients = *lowCoefficients;
        *leftChain.get<ChainPositions::lowMid>().coefficients = *lowMidCoefficients;
        *leftChain.get<ChainPositions::hiMid>().coefficients = *hiMidCoefficients;
//        *monoChain.get<ChainPositions::hi>().coefficients = *hiCoefficients;
        
        *rightChain.get<ChainPositions::lowMid>().coefficients = *lowMidCoefficients;
        *rightChain.get<ChainPositions::hiMid>().coefficients = *hiMidCoefficients;
        
        
    }

    void processBlock(juce::AudioSampleBuffer& buffer, juce::MidiBuffer&) override
    {
//        gain.setGainDecibels(ptr_apvts->getRawParameterValue("EQ_POST_GAIN")->load());
        auto eqSettings = getEQSettings(*ptr_apvts);
        auto lowCoefficients = juce::dsp::IIR::Coefficients<float>::makeLowShelf(getSampleRate(), eqSettings.lowFreq, eqSettings.lowQ, juce::Decibels::decibelsToGain(eqSettings.lowGainDecibels));
        auto lowMidCoefficients = juce::dsp::IIR::Coefficients<float>::makePeakFilter(getSampleRate(), eqSettings.lowMidFreq, eqSettings.lowMidQ, juce::Decibels::decibelsToGain(eqSettings.lowMidGainDecibels));
        auto hiMidCoefficients = juce::dsp::IIR::Coefficients<float>::makePeakFilter(getSampleRate(), eqSettings.hiMidFreq, eqSettings.hiMidQ, juce::Decibels::decibelsToGain(eqSettings.hiMidGainDecibels));
        auto hiCoefficients = juce::dsp::IIR::Coefficients<float>::makeHighShelf(getSampleRate(), eqSettings.hiFreq, eqSettings.hiQ, juce::Decibels::decibelsToGain(eqSettings.hiGainDecibels));
        
//        *monoChain.get<ChainPositions::low>().coefficients = *lowCoefficients;
        *leftChain.get<ChainPositions::lowMid>().coefficients = *lowMidCoefficients;
        *leftChain.get<ChainPositions::hiMid>().coefficients = *hiMidCoefficients;
//        *monoChain.get<ChainPositions::hi>().coefficients = *hiCoefficients;
        leftChain.get<ChainPositions::gain>().setGainDecibels(eqSettings.postGainDecibels);
        
        *rightChain.get<ChainPositions::lowMid>().coefficients = *lowMidCoefficients;
        *rightChain.get<ChainPositions::hiMid>().coefficients = *hiMidCoefficients;
        rightChain.get<ChainPositions::gain>().setGainDecibels(eqSettings.postGainDecibels);
        
        juce::dsp::AudioBlock<float> block(buffer);
        auto leftBlock = block.getSingleChannelBlock(0);
        auto rightBlock = block.getSingleChannelBlock(1);
        
        juce::dsp::ProcessContextReplacing<float> leftContext(leftBlock);
        juce::dsp::ProcessContextReplacing<float> rightContext(rightBlock);
        
        leftChain.process(leftContext);
        rightChain.process(rightContext);
//        gain.process(context);
    }

    void reset() override
    {
        leftChain.get<ChainPositions::gain>().reset();
        rightChain.get<ChainPositions::gain>().reset();
    }

    const juce::String getName() const override { return "Equalizer"; }

    juce::AudioProcessorValueTreeState* ptr_apvts;

private:
    using Gain = juce::dsp::Gain<float>;
    
    //Fitler design techniques based on tutorial at https:\/\/www.youtube.com/watch?v=i_Iq4_Kd7Rc
    using Filter = juce::dsp::IIR::Filter<float>;
    using CutFilter = juce::dsp::ProcessorChain<Filter, Filter, Filter, Filter>;
    using MonoChain = juce::dsp::ProcessorChain<Filter, Filter, Filter, Filter, Gain>;
    MonoChain leftChain, rightChain, monoChain;
    enum ChainPositions{
        low, lowMid, hiMid, hi, gain
    };

};
