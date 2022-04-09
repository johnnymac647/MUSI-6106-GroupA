/*
  ==============================================================================

    VerticalDiscreteMeter.h
    Created: 8 Apr 2022 11:49:11pm
    Author:  李克镰

  ==============================================================================
*/

#pragma once


#include <JuceHeader.h>


class VerticalDiscreteMeter : public juce::Component
{
public:
    void paint(juce::Graphics& g) override
    {
        auto bounds = getLocalBounds().toFloat();
        
        g.setColour(juce::Colours::white.withBrightness(0.4f));
        g.fillRoundedRectangle(bounds, 5.0f);
        g.setColour(juce::Colours::white);
        
        //map level from [-60.f, + 6.f] to [0, width]
        const auto scaledX = juce::jmap(mfLevel, -60.f, 6.f, 0.f, (float)getWidth() );
        
        g.fillRoundedRectangle(bounds.removeFromLeft(scaledX), 5.0f);
    }
    
    void setLevel(const float level)
    {
        mfLevel = level;
    }
    
private:
    float mfLevel = -60.f; //default level at minimum
};

