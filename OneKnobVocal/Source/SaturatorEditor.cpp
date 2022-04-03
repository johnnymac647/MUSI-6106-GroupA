/*
  ==============================================================================

    SaturatorEditor.cpp
    Created: 6 Feb 2022 4:51:40pm
    Author:  yinsile

  ==============================================================================
*/

#include "SaturatorEditor.h"

SaturatorEditor::SaturatorEditor(OneKnobVocalAudioProcessor& p)
    :AudioProcessorEditor(&p), mProcessor(p)
{
    for (int i = 0; i < Saturator::effectParameters::kNumOfParameters; i++)
    {
        editorLabels[i].setText(Saturator::parameterNames[i], juce::NotificationType::dontSendNotification);
        editorLabels[i].setBounds(0, i * 40 + 20, 120, 20);
        addAndMakeVisible(editorLabels[i]);

        flipToggleButtons[i].setClickingTogglesState(true);
        flipToggleButtons[i].setBounds(90, i * 40 + 20, 20, 20);
        flipToggleButtons[i].onClick = [this, i] { changeToggleStateOnClick(&flipToggleButtons[i]); };
        addAndMakeVisible(flipToggleButtons[i]);

        editorSliders[i].setSliderStyle(juce::Slider::SliderStyle::ThreeValueHorizontal);
        editorSliders[i].setTextBoxStyle(juce::Slider::TextBoxRight, true, 40, 20);
        editorSliders[i].addListener(this);
        addAndMakeVisible(editorSliders[i]);

        sliderAttachments[i] = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(mProcessor.apvts,
            Saturator::parameterIDs[i],
            editorSliders[i]);
        editorSliders[i].setMinAndMaxValues(mProcessor.knobValueMap[Saturator::parameterIDs[i]].start,
            mProcessor.knobValueMap[Saturator::parameterIDs[i]].end);
        editorSliders[i].setBounds(0, i * 40 + 40, 120, 20);
    }

    setAllButtonState();
    
}
SaturatorEditor::~SaturatorEditor()
{

}
void SaturatorEditor::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::darkgrey);

    g.setColour(juce::Colours::white);
    g.setFont(15.0f);
    g.drawFittedText("Saturator", getLocalBounds(), juce::Justification::centredTop, 1);
}

void SaturatorEditor::sliderValueChanged(juce::Slider* slider)
{
    for (int i = 0; i < Saturator::effectParameters::kNumOfParameters; i++)
    {
        if (slider == &editorSliders[i])
        {
            if (abs(slider->getMinValue() - mProcessor.knobValueMap[Saturator::parameterIDs[i]].start) > 1e-3
                || abs(slider->getMaxValue() - mProcessor.knobValueMap[Saturator::parameterIDs[i]].end) > 1e-3)
                mProcessor.knobValueMap.set(Saturator::parameterIDs[i],
                    ModdedNormalisableRange<float>(slider->getMinValue(), slider->getMaxValue()));
        }

    }
}

void SaturatorEditor::updateRanges()
{
    for (int i = 0; i < Saturator::effectParameters::kNumOfParameters; i++)
    {
        editorSliders[i].setMinAndMaxValues(mProcessor.knobValueMap[Saturator::parameterIDs[i]].start,
            mProcessor.knobValueMap[Saturator::parameterIDs[i]].end);
    }
}