/*
  ==============================================================================

    CompressorEditor.cpp
    Created: 6 Feb 2022 4:50:44pm
    Author:  yinsile

  ==============================================================================
*/

#include "CompressorEditor.h"

CompressorEditor::CompressorEditor(OneKnobVocalAudioProcessor& p)
    : mProcessor(p)
{
    for (int i = 0; i < Compressor::effectParameters::kNumOfParameters; i++)
    {
        editorLabels[i].setText(Compressor::parameterNames[i], juce::NotificationType::dontSendNotification);
        editorLabels[i].setBounds(0, i * 40 + 20, 120, 20);
        addAndMakeVisible(editorLabels[i]);

        flipToggleButtons[i].setClickingTogglesState(true);
        flipToggleButtons[i].setBounds(90, i * 40 + 20, 20, 20);
        flipToggleButtons[i].onClick = [this, i] { changeToggleStateOnClick(&flipToggleButtons[i]); };
        addAndMakeVisible(flipToggleButtons[i]);

        sliderAttachments[i] = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(mProcessor.apvts,
            Compressor::parameterIDs[i],
            editorSliders[i]);

        editorSliders[i].setSliderStyle(juce::Slider::SliderStyle::ThreeValueHorizontal);
        editorSliders[i].setTextBoxStyle(juce::Slider::TextBoxRight, true, 40, 20);

        editorSliders[i].setMinAndMaxValues(mProcessor.knobValueMap[Compressor::parameterIDs[i]].start,
            mProcessor.knobValueMap[Compressor::parameterIDs[i]].end);

        editorSliders[i].addListener(this);
        addAndMakeVisible(editorSliders[i]);


        editorSliders[i].setTooltip("Min: " + std::to_string(editorSliders[i].getMinValue()) + ", " + "Max: " + std::to_string(editorSliders[i].getMaxValue()));
        editorSliders[i].setBounds(0, i * 40 + 40, 120, 20);
    }

    setAllButtonState();
}
CompressorEditor::~CompressorEditor()
{

}
void CompressorEditor::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::orchid);

    g.setColour(juce::Colours::white);
    g.setFont(15.0f);
    g.drawFittedText("Compressor", getLocalBounds(), juce::Justification::centredTop, 1);
}

void CompressorEditor::sliderValueChanged(juce::Slider* slider)
{
    for (int i = 0; i < Compressor::effectParameters::kNumOfParameters; i++)
    {
        if (slider == &editorSliders[i])
        {
            if (abs(slider->getMinValue() - mProcessor.knobValueMap[Compressor::parameterIDs[i]].start) > 1e-3
                || abs(slider->getMaxValue() - mProcessor.knobValueMap[Compressor::parameterIDs[i]].end) > 1e-3)
            {
                mProcessor.knobValueMap.set(Compressor::parameterIDs[i],
                    ModdedNormalisableRange<double>(slider->getMinValue(), slider->getMaxValue()));
                editorSliders[i].setTooltip("Min: " + std::to_string(editorSliders[i].getMinValue()) + ", " + "Max: " + std::to_string(editorSliders[i].getMaxValue()));
            }
        }

    }
}

void CompressorEditor::updateRanges()
{
    for (int i = 0; i < Compressor::effectParameters::kNumOfParameters; i++)
    {
        editorSliders[i].setMinAndMaxValues(mProcessor.knobValueMap[Compressor::parameterIDs[i]].start,
            mProcessor.knobValueMap[Compressor::parameterIDs[i]].end);
        editorSliders[i].setTooltip("Min: " + std::to_string(editorSliders[i].getMinValue()) + ", " + "Max: " + std::to_string(editorSliders[i].getMaxValue()));
    }
}