/*
  ==============================================================================

    GateEditor.cpp
    Created: 6 Feb 2022 4:51:17pm
    Author:  yinsile

  ==============================================================================
*/

#include "GateEditor.h"

GateEditor::GateEditor(OneKnobVocalAudioProcessor& p)
    : mProcessor(p)
{
    for (int i = 0; i < Gate::effectParameters::kNumOfParameters; i++)
    {
        editorLabels[i].setText(Gate::parameterNames[i], juce::NotificationType::dontSendNotification);
        editorLabels[i].setBounds(0, i * 40 + 20, 120, 20);
        addAndMakeVisible(editorLabels[i]);

        flipToggleButtons[i].setClickingTogglesState(true);
        flipToggleButtons[i].setBounds(90, i * 40 + 20, 20, 20);
        flipToggleButtons[i].onClick = [this, i] { changeToggleStateOnClick(&flipToggleButtons[i]); };
        addAndMakeVisible(flipToggleButtons[i]);


        sliderAttachments[i] = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(mProcessor.apvts,
            Gate::parameterIDs[i],
            editorSliders[i]);

        editorSliders[i].setSliderStyle(juce::Slider::SliderStyle::ThreeValueHorizontal);
        editorSliders[i].setTextBoxStyle(juce::Slider::TextBoxRight, true, 40, 20);

        editorSliders[i].setMinAndMaxValues(mProcessor.knobValueMap[Gate::parameterIDs[i]].start,
            mProcessor.knobValueMap[Gate::parameterIDs[i]].end);

        editorSliders[i].addListener(this);
        addAndMakeVisible(editorSliders[i]);

        editorSliders[i].setTooltip("Min: " + std::to_string(editorSliders[i].getMinValue()) + ", " + "Max: " + std::to_string(editorSliders[i].getMaxValue()));
        editorSliders[i].setBounds(0, i * 40 + 40, 120, 20);
    }

    setAllButtonState();
}

GateEditor::~GateEditor()
{

}

void GateEditor::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::purple);

    g.setColour(juce::Colours::white);
    g.setFont(15.0f);
    g.drawFittedText("Gate", getLocalBounds(), juce::Justification::centredTop, 1);
}

void GateEditor::sliderValueChanged(juce::Slider* slider)
{
    for (int i = 0; i < Gate::effectParameters::kNumOfParameters; i++)
    {
        if (slider == &editorSliders[i])
        {
            if (abs(slider->getMinValue() - mProcessor.knobValueMap[Gate::parameterIDs[i]].start) > 1e-3
                || abs(slider->getMaxValue() - mProcessor.knobValueMap[Gate::parameterIDs[i]].end) > 1e-3)
            {
                mProcessor.knobValueMap.set(Gate::parameterIDs[i],
                    ModdedNormalisableRange<double>(slider->getMinValue(), slider->getMaxValue()));
                editorSliders[i].setTooltip("Min: " + std::to_string(editorSliders[i].getMinValue()) + ", " + "Max: " + std::to_string(editorSliders[i].getMaxValue()));
            }
        }

    }
}

void GateEditor::updateRanges()
{
    removeSliderListeners(this);
    for (int i = 0; i < Gate::effectParameters::kNumOfParameters; i++)
    {
        editorSliders[i].setMinAndMaxValues(mProcessor.knobValueMap[Gate::parameterIDs[i]].start,
            mProcessor.knobValueMap[Gate::parameterIDs[i]].end);
        editorSliders[i].setTooltip("Min: " + std::to_string(editorSliders[i].getMinValue()) + ", " + "Max: " + std::to_string(editorSliders[i].getMaxValue()));
    }
    addSliderListeners(this);
}