/*
  ==============================================================================

    GateEditor.cpp
    Created: 6 Feb 2022 4:51:17pm
    Author:  yinsile

  ==============================================================================
*/

#include "GateEditor.h"

GateEditor::GateEditor(OneKnobVocalAudioProcessor& p)
    :AudioProcessorEditor(&p), mProcessor(p)
{
    for (int i = 0; i < Gate::gateParameters::kNumOfParameters; i++)
    {
        editorLabels[i].setText(Gate::parameterNames[i], juce::NotificationType::dontSendNotification);
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
            Gate::parameterIDs[i],
            editorSliders[i]);
        editorSliders[i].setMinAndMaxValues(mProcessor.knobValueMap[Gate::parameterIDs[i]].start,
            mProcessor.knobValueMap[Gate::parameterIDs[i]].end);
        editorSliders[i].setBounds(0, i * 40 + 40, 120, 20);
    }

    /*int i = 1;

    VolumeButton.setClickingTogglesState(true);
    VolumeButton.setBounds(90, 20 * i, 20, 20);
    VolumeButton.onClick = [this] { changeToggleStateOnClick(&VolumeButton); };

    VolumeKnobLabel.setText("Post Gain", juce::NotificationType::dontSendNotification);
    VolumeKnobLabel.setBounds(0, 20 * (i++), 120, 20);
    addAndMakeVisible(VolumeKnobLabel);

    addAndMakeVisible(VolumeButton);

    VolumeKnob.setSliderStyle(juce::Slider::SliderStyle::ThreeValueHorizontal);
    VolumeKnob.setTextBoxStyle(juce::Slider::TextBoxRight, true, 40, 20);
    VolumeKnob.addListener(this);
    addAndMakeVisible(VolumeKnob);
    VolumeKnobAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(mProcessor.apvts, "GATE_POST_GAIN", VolumeKnob);
    VolumeKnob.setMinAndMaxValues(mProcessor.knobValueMap["GATE_POST_GAIN"].start, mProcessor.knobValueMap["GATE_POST_GAIN"].end);
    VolumeKnob.setBounds(0, 20 * (i++), 120, 20);


    ThresholdButton.setClickingTogglesState(true);
    ThresholdButton.setBounds(90, 20 * i, 20, 20);
    ThresholdButton.onClick = [this] { changeToggleStateOnClick(&ThresholdButton); };

    ThresholdKnobLabel.setText("Threshold", juce::NotificationType::dontSendNotification);
    ThresholdKnobLabel.setBounds(0, 20 * (i++), 120, 20);
    addAndMakeVisible(ThresholdKnobLabel);

    addAndMakeVisible(ThresholdButton);

    ThresholdKnob.setSliderStyle(juce::Slider::SliderStyle::ThreeValueHorizontal);
    ThresholdKnob.setTextBoxStyle(juce::Slider::TextBoxRight, true, 40, 20);
    ThresholdKnob.addListener(this);
    addAndMakeVisible(ThresholdKnob);
    ThresholdKnobAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(mProcessor.apvts, "GATE_THRESHOLD", ThresholdKnob);
    ThresholdKnob.setMinAndMaxValues(mProcessor.knobValueMap["GATE_THRESHOLD"].start, mProcessor.knobValueMap["GATE_THRESHOLD"].end);
    ThresholdKnob.setBounds(0, 20 * (i++), 120, 20);

    RatioButton.setClickingTogglesState(true);
    RatioButton.setBounds(90, 20 * i, 20, 20);
    RatioButton.onClick = [this] { changeToggleStateOnClick(&RatioButton); };

    RatioKnobLabel.setText("Ratio", juce::NotificationType::dontSendNotification);
    RatioKnobLabel.setBounds(0, 20 * (i++), 120, 20);
    addAndMakeVisible(RatioKnobLabel);

    addAndMakeVisible(RatioButton);

    RatioKnob.setSliderStyle(juce::Slider::SliderStyle::ThreeValueHorizontal);
    RatioKnob.setTextBoxStyle(juce::Slider::TextBoxRight, true, 40, 20);
    RatioKnob.addListener(this);
    addAndMakeVisible(RatioKnob);
    RatioKnobAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(mProcessor.apvts, "GATE_RATIO", RatioKnob);
    RatioKnob.setMinAndMaxValues(mProcessor.knobValueMap["GATE_RATIO"].start, mProcessor.knobValueMap["GATE_RATIO"].end);
    RatioKnob.setBounds(0, 20 * (i++), 120, 20);

    AttackButton.setClickingTogglesState(true);
    AttackButton.setBounds(90, 20 * i, 20, 20);
    AttackButton.onClick = [this] { changeToggleStateOnClick(&AttackButton); };

    AttackKnobLabel.setText("Attack", juce::NotificationType::dontSendNotification);
    AttackKnobLabel.setBounds(0, 20 * (i++), 120, 20);
    addAndMakeVisible(AttackKnobLabel);

    addAndMakeVisible(AttackButton);

    AttackKnob.setSliderStyle(juce::Slider::SliderStyle::ThreeValueHorizontal);
    AttackKnob.setTextBoxStyle(juce::Slider::TextBoxRight, true, 40, 20);
    AttackKnob.addListener(this);
    addAndMakeVisible(AttackKnob);
    AttackKnobAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(mProcessor.apvts, "GATE_ATTACK", AttackKnob);
    AttackKnob.setMinAndMaxValues(mProcessor.knobValueMap["GATE_ATTACK"].start, mProcessor.knobValueMap["GATE_ATTACK"].end);
    AttackKnob.setBounds(0, 20 * (i++), 120, 20);

    ReleaseButton.setClickingTogglesState(true);
    ReleaseButton.setBounds(90, 20 * i, 20, 20);
    ReleaseButton.onClick = [this] { changeToggleStateOnClick(&ReleaseButton); };

    ReleaseKnobLabel.setText("Release", juce::NotificationType::dontSendNotification);
    ReleaseKnobLabel.setBounds(0, 20 * (i++), 120, 20);
    addAndMakeVisible(ReleaseKnobLabel);

    addAndMakeVisible(ReleaseButton);

    ReleaseKnob.setSliderStyle(juce::Slider::SliderStyle::ThreeValueHorizontal);
    ReleaseKnob.setTextBoxStyle(juce::Slider::TextBoxRight, true, 40, 20);
    ReleaseKnob.addListener(this);
    addAndMakeVisible(ReleaseKnob);
    ReleaseKnobAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(mProcessor.apvts, "GATE_RELEASE", ReleaseKnob);
    ReleaseKnob.setMinAndMaxValues(mProcessor.knobValueMap["GATE_RELEASE"].start, mProcessor.knobValueMap["GATE_RELEASE"].end);
    ReleaseKnob.setBounds(0, 20 * (i++), 120, 20);*/

    setAllButtonState();
}

GateEditor::~GateEditor()
{

}

void GateEditor::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::crimson);

    g.setColour(juce::Colours::white);
    g.setFont(15.0f);
    g.drawFittedText("Gate", getLocalBounds(), juce::Justification::centredTop, 1);
}

void GateEditor::sliderValueChanged(juce::Slider* slider)
{

    for (int i = 0; i < Gate::gateParameters::kNumOfParameters; i++)
    {
        if (slider == &editorSliders[i])
        {
            if (abs(slider->getMinValue() - mProcessor.knobValueMap[Gate::parameterIDs[i]].start) > 1e-3
                || abs(slider->getMaxValue() - mProcessor.knobValueMap[Gate::parameterIDs[i]].end) > 1e-3)
                mProcessor.knobValueMap.set(Gate::parameterIDs[i],
                    ModdedNormalisableRange<float>(slider->getMinValue(), slider->getMaxValue()));
        }

    }

    //if (slider == &VolumeKnob)
    //{
    //    if (abs(VolumeKnob.getMinValue() - mProcessor.knobValueMap["GATE_POST_GAIN"].start) < 1e-3 || abs(VolumeKnob.getMaxValue() - mProcessor.knobValueMap["GATE_POST_GAIN"].end) < 1e-3)
    //        mProcessor.knobValueMap.set("GATE_POST_GAIN", ModdedNormalisableRange<float>(VolumeKnob.getMinValue(), VolumeKnob.getMaxValue()));
    //}
    //else if (slider == &ThresholdKnob)
    //{
    //    if (abs(ThresholdKnob.getMinValue() - mProcessor.knobValueMap["GATE_THRESHOLD"].start) < 1e-3 || abs(ThresholdKnob.getMaxValue() - mProcessor.knobValueMap["GATE_THRESHOLD"].end) < 1e-3)
    //        mProcessor.knobValueMap.set("GATE_THRESHOLD", ModdedNormalisableRange<float>(ThresholdKnob.getMinValue(), ThresholdKnob.getMaxValue()));
    //}
    //else if (slider == &RatioKnob)
    //{
    //    if (abs(RatioKnob.getMinValue() - mProcessor.knobValueMap["GATE_RATIO"].start) < 1e-3 || abs(RatioKnob.getMaxValue() - mProcessor.knobValueMap["GATE_RATIO"].end) < 1e-3)
    //        mProcessor.knobValueMap.set("GATE_RATIO", ModdedNormalisableRange<float>(RatioKnob.getMinValue(), RatioKnob.getMaxValue()));
    //}
    //else if (slider == &AttackKnob)
    //{
    //    if (abs(AttackKnob.getMinValue() - mProcessor.knobValueMap["GATE_ATTACK"].start) < 1e-3 || abs(AttackKnob.getMaxValue() - mProcessor.knobValueMap["GATE_ATTACK"].end) < 1e-3)
    //        mProcessor.knobValueMap.set("GATE_ATTACK", ModdedNormalisableRange<float>(AttackKnob.getMinValue(), AttackKnob.getMaxValue()));
    //}
    //else if (slider == &ReleaseKnob)
    //{
    //    if (abs(ReleaseKnob.getMinValue() - mProcessor.knobValueMap["GATE_RELEASE"].start) < 1e-3 || abs(ReleaseKnob.getMaxValue() - mProcessor.knobValueMap["GATE_RELEASE"].end) < 1e-3)
    //        mProcessor.knobValueMap.set("GATE_RELEASE", ModdedNormalisableRange<float>(ReleaseKnob.getMinValue(), ReleaseKnob.getMaxValue()));
    //}
}

void GateEditor::updateRanges()
{
    for (int i = 0; i < Gate::gateParameters::kNumOfParameters; i++)
    {
        editorSliders[i].setMinAndMaxValues(mProcessor.knobValueMap[Gate::parameterIDs[i]].start,
            mProcessor.knobValueMap[Gate::parameterIDs[i]].end);
    }

    /*VolumeKnob.setMinAndMaxValues(mProcessor.knobValueMap["GATE_POST_GAIN"].start, mProcessor.knobValueMap["GATE_POST_GAIN"].end);
    ThresholdKnob.setMinAndMaxValues(mProcessor.knobValueMap["GATE_THRESHOLD"].start, mProcessor.knobValueMap["GATE_THRESHOLD"].end);
    RatioKnob.setMinAndMaxValues(mProcessor.knobValueMap["GATE_RATIO"].start, mProcessor.knobValueMap["GATE_RATIO"].end);
    AttackKnob.setMinAndMaxValues(mProcessor.knobValueMap["GATE_ATTACK"].start, mProcessor.knobValueMap["GATE_ATTACK"].end);
    ReleaseKnob.setMinAndMaxValues(mProcessor.knobValueMap["GATE_RELEASE"].start, mProcessor.knobValueMap["GATE_RELEASE"].end);*/
}