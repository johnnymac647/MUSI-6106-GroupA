/*
  ==============================================================================

    DeEsserEditor.cpp
    Created: 6 Feb 2022 4:50:53pm
    Author:  yinsile

  ==============================================================================
*/

#include "DeEsserEditor.h"

DeEsserEditor::DeEsserEditor(OneKnobVocalAudioProcessor& p)
    :AudioProcessorEditor(&p), mProcessor(p)
{
    for (int i = 0; i < Deesser::effectParameters::kNumOfParameters; i++)
    {
        editorLabels[i].setText(Deesser::parameterNames[i], juce::NotificationType::dontSendNotification);
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
            Deesser::parameterIDs[i],
            editorSliders[i]);
        editorSliders[i].setMinAndMaxValues(mProcessor.knobValueMap[Deesser::parameterIDs[i]].start,
            mProcessor.knobValueMap[Deesser::parameterIDs[i]].end);
        editorSliders[i].setBounds(0, i * 40 + 40, 120, 20);
    }

    setAllButtonState();

}

DeEsserEditor::~DeEsserEditor()
{

}

void DeEsserEditor::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::orchid);

    g.setColour(juce::Colours::white);
    g.setFont(15.0f);
    g.drawFittedText("De-Esser", getLocalBounds(), juce::Justification::centredTop, 1);
}

void DeEsserEditor::sliderValueChanged(juce::Slider* slider)
{
    for (int i = 0; i < Deesser::effectParameters::kNumOfParameters; i++)
    {
        if (slider == &editorSliders[i])
        {
            if (abs(slider->getMinValue() - mProcessor.knobValueMap[Deesser::parameterIDs[i]].start) > 1e-3
                || abs(slider->getMaxValue() - mProcessor.knobValueMap[Deesser::parameterIDs[i]].end) > 1e-3)
                mProcessor.knobValueMap.set(Deesser::parameterIDs[i],
                    ModdedNormalisableRange<double>(slider->getMinValue(), slider->getMaxValue()));
        }

    }
}

void DeEsserEditor::updateRanges()
{
    for (int i = 0; i < Deesser::effectParameters::kNumOfParameters; i++)
    {
        editorSliders[i].setMinAndMaxValues(mProcessor.knobValueMap[Deesser::parameterIDs[i]].start,
            mProcessor.knobValueMap[Deesser::parameterIDs[i]].end);
    }
}