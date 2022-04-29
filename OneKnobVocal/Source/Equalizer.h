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
#include "ModdedNormalisableRange.h"




class Equalizer : public ProcessorBase
{
public:
    enum effectParameters
    {
        kPostGain = 0,
        kLowBandGain,
        kLowBandCutoff,
        kLowBandQ,
        kLowMidBandGain,
        kLowMidBandFreq,
        kLowMidBandQ,
        kHighMidBandGain,
        kHighMidBandFreq,
        kHighMidBandQ,
        kHighBandGain,
        kHighBandCutoff,
        kHighBandQ,
        kNumOfParameters
    };

    inline static const juce::String parameterIDs[effectParameters::kNumOfParameters]
    {
        "EQ_POST_GAIN",
        "EQ_LOW_BAND_GAIN",
        "EQ_LOW_BAND_CUTOFF",
        "EQ_LOW_BAND_QF",
        "EQ_LOWMID_BAND_GAIN",
        "EQ_LOWMID_BAND_FREQ",
        "EQ_LOWMID_BAND_QF",
        "EQ_HIMID_BAND_GAIN",
        "EQ_HIMID_BAND_FREQ",
        "EQ_HIMID_BAND_QF",
        "EQ_HI_BAND_GAIN",
        "EQ_HI_BAND_CUTOFF",
        "EQ_HI_BAND_QF"
    };

    inline static const juce::String parameterNames[effectParameters::kNumOfParameters]
    {
        "Post Gain",
        "Low Gain",
        "Low Cutoff",
        "Low Q",
        "Low-mid Gain",
        "Low-mid Freq",
        "Low-mid Q",
        "Hi-mid Gain",
        "Hi-mid Freq",
        "Hi-mid Q",
        "High Gain",
        "High Cutoff",
        "High Q"
    };

    inline static const float parameterSettings[effectParameters::kNumOfParameters][parameterRange::kParameterRangeNumbers]
    {
        {-96.0f, 12.0f, 0.0f},
        {-24.0f, 12.0f, 0.0f},
        {50.0f, 200.0f, 100.0f},
        {0.01f, 10.0f, 0.71f},
        {-24.0f, 12.0f, 0.0f},
        {100.0f, 2000.0f, 400.0f},
        {0.01f, 10.0f, 0.71f},
        {-24.0f, 12.0f, 0.0f},
        {800.0f, 8000.0f, 1000.0f},
        {0.01f, 10.0f, 0.71f},
        {-24.0f, 12.0f, 0.0f},
        {2000.0f, 16000.0f, 8000.0f},
        {0.01f, 10.0f, 0.71f},
    };

    static void addToParameterLayout(std::vector<std::unique_ptr<juce::RangedAudioParameter>>& params)
    {
        for (int i = 0; i < effectParameters::kNumOfParameters; i++)
        {
            params.push_back(std::make_unique<juce::AudioParameterFloat>(parameterIDs[i],
                "EQ " + parameterNames[i],
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

    struct EQSettings {
        float postGainDecibels{ 0 }, lowGainDecibels{ 0 }, lowMidGainDecibels{ 0 }, hiMidGainDecibels{ 0 }, hiGainDecibels{ 0 };
        float lowQ{ 0 }, lowMidQ{ 0 }, hiMidQ{ 0 }, hiQ{ 0 };
        float lowFreq{ 0 }, lowMidFreq{ 0 }, hiMidFreq{ 0 }, hiFreq{ 0 };
    };

    EQSettings getEQSettings(const juce::AudioProcessorValueTreeState& apvts);

};
