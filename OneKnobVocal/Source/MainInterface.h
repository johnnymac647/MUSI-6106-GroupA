/*
  ==============================================================================

    MainInterface.h
    Created: 13 Apr 2022 12:18:33pm
    Author:  JOHN MCNAMARA

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class MainInterface  : public juce::AudioAppComponent,
                        public juce::Slider::Listener
{
public:
    MainInterface();
    ~MainInterface() override;

    //==============================================================================
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;

    //==============================================================================
    void paint (juce::Graphics& g) override;
    void resized() override;
    void sliderValueChanged (juce::Slider* slider) override;
    
    
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainInterface)
    
    juce::LookAndFeel_V4 royalTheme;
    
    juce::Colour backgroundColor = juce::Colour(0xff0f0038); //dark purple
    juce::Colour textColor = juce::Colour(0xffc2b948); // gold
    juce::Colour darkGold = juce::Colour(0xff423E12); //darkGold
    juce::Colour clear = juce::Colour(0x00000000);
    
    juce::Slider knob;
    juce::Label knobLabel;
    
    juce::String s_knobValue;
};
