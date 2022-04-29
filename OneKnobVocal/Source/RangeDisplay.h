/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 6.1.6

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library.
  Copyright (c) 2020 - Raw Material Software Limited.

  ==============================================================================
*/

#pragma once

//[Headers]     -- You can add your own extra header files here --
#include <JuceHeader.h>
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class RangeDisplay  : public juce::Component,
    private juce::Timer
{
public:
    //==============================================================================
    /** Creates a tooltip window.
        Make sure your app only creates one instance of this class, otherwise you'll
        get multiple overlaid tooltips appearing. The window will initially be invisible
        and will make itself visible when it needs to display a tip.
        To change the style of tooltips, see the LookAndFeel class for its tooltip
        methods.
        @param parentComponent  if set to nullptr, the TooltipWindow will appear on the desktop,
                                otherwise the tooltip will be added to the given parent
                                component.
        @param millisecondsBeforeTipAppears     the time for which the mouse has to stay still
                                                before a tooltip will be shown
        @see TooltipClient, LookAndFeel::drawTooltip, LookAndFeel::getTooltipBounds
    */
    explicit RangeDisplay(Component* parentComponent = nullptr);

    /** Destructor. */
    ~RangeDisplay() override;



    /** Can be called to manually force a tip to be shown at a particular location.
        The tip will be shown until hideTip() is called, or a dismissal mouse event
        occurs.
        @see hideTip
    */
    void displayTip(juce::Point<int> screenPosition, const juce::String& text);

    /** Can be called to manually hide the tip if it's showing. */
    void hideTip();

    /** Asks a component for its tooltip.
        This can be overridden if you need custom lookup behaviour or to modify the strings.
    */
    virtual juce::String getTipFor(Component&);

    //==============================================================================
    /** A set of colour IDs to use to change the colour of various aspects of the tooltip.
        These constants can be used either via the Component::setColour(), or LookAndFeel::setColour()
        methods.
        @see Component::setColour, Component::findColour, LookAndFeel::setColour, LookAndFeel::findColour
    */
    enum ColourIds
    {
        backgroundColourId = 0x1001b00,    /**< The colour to fill the background with. */
        textColourId = 0x1001c00,    /**< The colour to use for the text. */
        outlineColourId = 0x1001c10     /**< The colour to use to draw an outline around the tooltip. */
    };

    //==============================================================================
    /** This abstract base class is implemented by LookAndFeel classes to provide
        window drawing functionality.
    */
    struct JUCE_API  LookAndFeelMethods
    {
        virtual ~LookAndFeelMethods() = default;

        /** returns the bounds for a tooltip at the given screen coordinate, constrained within the given desktop area. */
        virtual juce::Rectangle<int> getTooltipBounds(const juce::String& tipText, juce::Point<int> screenPos, juce::Rectangle<int> parentArea) = 0;
        virtual void drawTooltip(juce::Graphics&, const juce::String& text, int width, int height) = 0;
    };

    //==============================================================================
    /** @internal */
    float getDesktopScaleFactor() const override;

private:
    //==============================================================================
    juce::Point<float> lastMousePos;
    SafePointer<Component> lastComponentUnderMouse;
    juce::String tipShowing, lastTipUnderMouse, manuallyShownTip;
    int millisecondsBeforeTipAppears;
    unsigned int lastCompChangeTime = 0, lastHideTime = 0;
    bool reentrant = false, dismissalMouseEventOccurred = false;

    enum ShownManually { yes, no };
    void displayTipInternal(juce::Point<int>, const juce::String&, ShownManually);

    std::unique_ptr<juce::AccessibilityHandler> createAccessibilityHandler() override;
    void paint(juce::Graphics&) override;
    void mouseEnter(const juce::MouseEvent&) override;
    void mouseDown(const juce::MouseEvent&) override;
    void mouseWheelMove(const juce::MouseEvent&, const juce::MouseWheelDetails&) override;
    void updatePosition(const juce::String&, juce::Point<int>, juce::Rectangle<int>);

    void timerCallback() override;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(RangeDisplay)

};

//[EndFile] You can add extra defines here...
//[/EndFile]

