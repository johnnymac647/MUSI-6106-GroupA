/*
  ==============================================================================

    VerticalMeter.h
    Created: 8 Apr 2022 11:49:11pm
    Author:  李克镰

  ==============================================================================
*/

#pragma once


#include <JuceHeader.h>


class Bulb
:   public juce::Component
{
public:
    Bulb(const juce::Colour& c) : colour(c){}
    
    
    void setState(const bool state)
    {
        isOn = state;
    }
    
    
    void paint(juce::Graphics& g) override
    {
        //some of the code can be moved to resized(), but I don't know which...
        const auto delta = 2.f;
        const auto bounds = getLocalBounds().toFloat().reduced(delta);
        const auto side = juce::jmin(bounds.getWidth(), bounds.getHeight());
        const auto bulbFillBounds = juce::Rectangle<float>(bounds.getX(), bounds.getY(), side, side);
        
        if (isOn)
            g.setColour(colour);
        else
            g.setColour(juce::Colours::black);
        
        g.fillEllipse(bulbFillBounds);
        
        g.setColour(juce::Colours::black);
        g.drawEllipse(bulbFillBounds, 1.f);
        
        
        if (isOn)
        {
            g.setGradientFill(juce::ColourGradient{colour.withAlpha(0.3f),
                                                   bulbFillBounds.getCentre(),
                                                   colour.withLightness(1.5f).withAlpha(0.f),
                                                   {},
                                                   true
            });
            
            g.fillEllipse(bulbFillBounds.expanded(delta));
            
        }
    }
    

private:
    bool isOn = false;
    juce::Colour colour{};
    
};



class VerticalMeter
:   public juce::Component

{
public:
    void paint(juce::Graphics& g) override
    {
        
        
//        auto bounds = getLocalBounds().toFloat();
//
//        g.setColour(juce::Colours::black);
//        g.fillRect(bounds);
//
//        g.setGradientFill(gradient);
//        const auto scaledY = juce::jmap(mfLevel, -60.f, 6.f, 0.f, (float)getHeight());
//        g.fillRect(bounds.removeFromBottom(scaledY));
        
        float fGain = juce::jmap(mfLevel, -60.f, 6.f, 0.f, 1.f);
        
        for (int i=0; i<iNumOfBulbs; i++)
        {
            if(fGain >= (float)(i+1)/iNumOfBulbs)
                bulbs[i]->setState(true);
            else
                bulbs[i]->setState(false);
        }
    }
    
    
    void resized() override
        {
            const auto bounds = getLocalBounds().toFloat();
            
            gradient = juce::ColourGradient{
                juce::Colours::green,
                bounds.getBottomLeft(),
                juce::Colours::red,
                bounds.getTopLeft(),
                false //linear gradient
            };
            
            gradient.addColour(0.5, juce::Colours::yellow);
            
            auto bulbBounds = getLocalBounds();
            const auto bulbHeight = bulbBounds.getHeight() / iNumOfBulbs;
            bulbs.clear();
            
            for (int i=0; i<iNumOfBulbs; i++){
                //create a bulb and set colour
                auto bulb = std::make_unique<Bulb>(gradient.getColourAtPosition( (double)(i)/iNumOfBulbs ));
                addAndMakeVisible(bulb.get());
                bulb->setBounds(bulbBounds.removeFromBottom(bulbHeight));
                //add the bulb to the vector
                bulbs.push_back(std::move(bulb)); //move is more efficient
            }
        }
    
    
    void setLevel(const float level)
    {
        mfLevel = level;
    }
    
private:
    float mfLevel = -60.f; //default level at minimum
    
    //because juce component is not copyable or moveable, cannot be in a vector (resize!)
    //the workaround is unique_ptr
    std::vector<std::unique_ptr<Bulb>> bulbs;
    const int iNumOfBulbs = 10;
    juce::ColourGradient gradient{};
};

