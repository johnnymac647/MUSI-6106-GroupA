/*
  ==============================================================================

    MainInterface.cpp
    Created: 13 Apr 2022 12:18:33pm
    Author:  JOHN MCNAMARA

  ==============================================================================
*/

#include <JuceHeader.h>
#include "MainInterface.h"

//==============================================================================
MainInterface::MainInterface()
{
    // Make sure you set the size of the component after
    // you add any child components.
    setSize (800, 600);

    // Some platforms require permissions to open input channels so request that here
//    if (juce::RuntimePermissions::isRequired (juce::RuntimePermissions::recordAudio)
//        && ! juce::RuntimePermissions::isGranted (juce::RuntimePermissions::recordAudio))
//    {
//        juce::RuntimePermissions::request (juce::RuntimePermissions::recordAudio,
//                                           [&] (bool granted) { setAudioChannels (granted ? 2 : 0, 2); });
//    }
//    else
//    {
//        // Specify the number of input and output channels that we want to open
//        setAudioChannels (2, 2);
//    }
    
    
    addAndMakeVisible(knob);
    knob.setSliderStyle(juce::Slider::Rotary);
    knob.setTextBoxStyle(juce::Slider::NoTextBox, true, 50, 10);
    knob.setRange(0, 100);
    knob.addListener(this);
    
    addAndMakeVisible(knobLabel);
//    knobLabel.setText("Value", juce::dontSendNotification);
    knobLabel.attachToComponent(&knob, true);
    
    royalTheme.setColour(juce::Slider::thumbColourId, textColor);
    royalTheme.setColour(juce::Slider::textBoxTextColourId, textColor);
    royalTheme.setColour(juce::Slider::rotarySliderFillColourId, textColor);
    royalTheme.setColour(juce::Slider::rotarySliderOutlineColourId, darkGold);
    royalTheme.setColour(juce::Slider::textBoxOutlineColourId, clear);
    
    knob.setLookAndFeel(&royalTheme);

}

MainInterface::~MainInterface()
{
}

void MainInterface::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll(backgroundColor);
    g.setColour(textColor);
    g.drawText("Voce Dolce", getWidth()/2 - 100, 50, 200, 20, juce::Justification::centred, true);
}

void MainInterface::resized()
{
    // This is called when the MainContentComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
    auto sliderWidth = 300;
    knob.setBounds ((getWidth() - sliderWidth)/2 - 10, (getHeight() - sliderWidth)/2, sliderWidth, sliderWidth);
}

void MainComponent::sliderValueChanged(juce::Slider *slider){
    if(slider == &knob){
        s_knobValue = juce::String( knob.getValue() );
//        g.drawText(s_knobValue, getBounds())
    }
}
