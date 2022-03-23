/*
  ==============================================================================

    EqualizerEditor.h
    Created: 6 Feb 2022 4:51:05pm
    Author:  yinsile

  ==============================================================================
*/

#pragma once
#include "PluginProcessor.h"
class EqualizerEditor : public juce::AudioProcessorEditor,
    public juce::Slider::Listener
{
public:
    EqualizerEditor(OneKnobVocalAudioProcessor&);
    ~EqualizerEditor() override;
    void paint(juce::Graphics&) override;
    void sliderValueChanged(juce::Slider* slider) override;
    void updateRanges();
private:
    OneKnobVocalAudioProcessor& mProcessor;


    juce::Slider PostGainKnob;
    juce::Label PostGainLabel;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> PostGainKnobAttach;

    juce::Slider LowBandGainKnob;
    juce::Label LowBandGainKnobLabel;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> LowBandGainKnobAttach;

    juce::Slider LowBandCutoffKnob;
    juce::Label LowBandCutoffKnobLabel;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> LowBandCutoffKnobAttach;

    juce::Slider LowBandQualityKnob;
    juce::Label LowBandQualityKnobLabel;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> LowBandQualityKnobAttach;

    juce::Slider LowMidBandGainKnob;
    juce::Label LowMidBandGainKnobLabel;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> LowMidBandGainKnobAttach;

    juce::Slider LowMidBandFreqKnob;
    juce::Label LowMidBandFreqKnobLabel;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> LowMidBandFreqKnobAttach;

    juce::Slider LowMidBandQualityKnob;
    juce::Label LowMidBandQualityKnobLabel;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> LowMidBandQualityKnobAttach;

    juce::Slider HighMidBandGainKnob;
    juce::Label HighMidBandGainKnobLabel;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> HighMidBandGainKnobAttach;

    juce::Slider HighMidBandFreqKnob;
    juce::Label HighMidBandFreqKnobLabel;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> HighMidBandFreqKnobAttach;

    juce::Slider HighMidBandQualityKnob;
    juce::Label HighMidBandQualityKnobLabel;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> HighMidBandQualityKnobAttach;

    juce::Slider HighBandGainKnob;
    juce::Label HighBandGainKnobLabel;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> HighBandGainKnobAttach;

    juce::Slider HighBandCutoffKnob;
    juce::Label HighBandCutoffKnobLabel;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> HighBandCutoffKnobAttach;

    juce::Slider HighBandQualityKnob;
    juce::Label HighBandQualityKnobLabel;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> HighBandQualityKnobAttach;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(EqualizerEditor);
};
