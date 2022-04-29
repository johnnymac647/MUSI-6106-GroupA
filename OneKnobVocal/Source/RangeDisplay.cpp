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

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "RangeDisplay.h"


RangeDisplay::RangeDisplay(Component* parentComp)
    : Component("tooltip"),
    millisecondsBeforeTipAppears(0)
{
    setAlwaysOnTop(true);
    setOpaque(true);
    setAccessible(false);

    if (parentComp != nullptr)
        parentComp->addChildComponent(this);

    auto& desktop = juce::Desktop::getInstance();

    if (desktop.getMainMouseSource().canHover())
    {
        desktop.addGlobalMouseListener(this);
        startTimer(123);
    }
}

RangeDisplay::~RangeDisplay()
{
    hideTip();
    juce::Desktop::getInstance().removeGlobalMouseListener(this);
}

void RangeDisplay::paint(juce::Graphics& g)
{
    getLookAndFeel().drawTooltip(g, tipShowing, getWidth(), getHeight());
}

void RangeDisplay::mouseEnter(const juce::MouseEvent& e)
{
    if (e.eventComponent == this)
        hideTip();
}

void RangeDisplay::mouseDown(const juce::MouseEvent&)
{
    //if (isVisible())
    //    dismissalMouseEventOccurred = true;
}

void RangeDisplay::mouseWheelMove(const juce::MouseEvent&, const juce::MouseWheelDetails&)
{
    if (isVisible())
        dismissalMouseEventOccurred = true;
}

void RangeDisplay::updatePosition(const juce::String& tip, juce::Point<int> pos, juce::Rectangle<int> parentArea)
{
    setBounds(getLookAndFeel().getTooltipBounds(tip, pos, parentArea));
    setVisible(true);
}



void RangeDisplay::displayTip(juce::Point<int> screenPos, const juce::String& tip)
{
    jassert(tip.isNotEmpty());

    displayTipInternal(screenPos, tip, ShownManually::yes);
}

void RangeDisplay::displayTipInternal(juce::Point<int> screenPos, const juce::String& tip, ShownManually shownManually)
{
    if (!reentrant)
    {
        juce::ScopedValueSetter<bool> setter(reentrant, true, false);

        if (tipShowing != tip)
        {
            tipShowing = tip;
            repaint();
        }

        if (auto* parent = getParentComponent())
        {
            updatePosition(tip, juce::Point<int>(-40, 780),
                parent->getLocalBounds());
        }
        else
        {
            //const auto physicalPos = ScalingHelpers::scaledScreenPosToUnscaled(screenPos);
            //const auto scaledPos = ScalingHelpers::unscaledScreenPosToScaled(*this, physicalPos);
            //updatePosition(tip, scaledPos, juce::Desktop::getInstance().getDisplays().getDisplayForPoint(screenPos)->userArea);

            addToDesktop(juce::ComponentPeer::windowHasDropShadow
                | juce::ComponentPeer::windowIsTemporary
                | juce::ComponentPeer::windowIgnoresKeyPresses
                | juce::ComponentPeer::windowIgnoresMouseClicks);
        }

        toFront(false);
        manuallyShownTip = shownManually == ShownManually::yes ? tip : juce::String();
        dismissalMouseEventOccurred = false;
    }
}

juce::String RangeDisplay::getTipFor(juce::Component& c)
{
    //if (juce::isForegroundOrEmbeddedProcess(&c)
    //    && !juce::ModifierKeys::currentModifiers.isAnyMouseButtonDown())
    //{
    //    if (auto* ttc = dynamic_cast<juce::TooltipClient*> (&c))
    //        if (!c.isCurrentlyBlockedByAnotherModalComponent())
    //            return ttc->getTooltip();
    //}

    //return {};

    if (auto* ttc = dynamic_cast<juce::TooltipClient*> (&c))
        if (!c.isCurrentlyBlockedByAnotherModalComponent())
            return ttc->getTooltip();

    return {};
}

void RangeDisplay::hideTip()
{
    if (isVisible() && !reentrant)
    {
        tipShowing = {};
        manuallyShownTip = {};
        dismissalMouseEventOccurred = false;

        removeFromDesktop();
        setVisible(false);

    }
}

float RangeDisplay::getDesktopScaleFactor() const
{
    if (lastComponentUnderMouse != nullptr)
        return Component::getApproximateScaleFactorForComponent(lastComponentUnderMouse);

    return Component::getDesktopScaleFactor();
}

std::unique_ptr<juce::AccessibilityHandler> RangeDisplay::createAccessibilityHandler()
{
    return createIgnoredAccessibilityHandler(*this);
}

void RangeDisplay::timerCallback()
{
    const auto mouseSource = juce::Desktop::getInstance().getMainMouseSource();
    auto* newComp = mouseSource.isTouch() ? nullptr : mouseSource.getComponentUnderMouse();

    if (manuallyShownTip.isNotEmpty())
    {
        if (dismissalMouseEventOccurred || newComp == nullptr)
            hideTip();

        return;
    }

    if (newComp == nullptr || getParentComponent() == nullptr || newComp->getPeer() == getPeer())
    {
        const auto newTip = newComp != nullptr ? getTipFor(*newComp) : juce::String();

        const auto mousePos = mouseSource.getScreenPosition();
        const auto mouseMovedQuickly = (mousePos.getDistanceFrom(lastMousePos) > 12);
        lastMousePos = mousePos;

        const auto tipChanged = (newTip != lastTipUnderMouse || newComp != lastComponentUnderMouse);
        const auto now = juce::Time::getApproximateMillisecondCounter();

        lastComponentUnderMouse = newComp;
        lastTipUnderMouse = newTip;

        if (tipChanged || dismissalMouseEventOccurred || mouseMovedQuickly)
            lastCompChangeTime = now;

        const auto showTip = [this, &mouseSource, &mousePos, &newTip]
        {
            if (mouseSource.getLastMouseDownPosition() != lastMousePos)
                displayTipInternal(mousePos.roundToInt(), newTip, ShownManually::no);
        };

        if (isVisible() || now < lastHideTime + 500)
        {
            // if a tip is currently visible (or has just disappeared), update to a new one
            // immediately if needed..
            if (newComp == nullptr || dismissalMouseEventOccurred || newTip.isEmpty())
                hideTip();
            else if (tipChanged)
                showTip();
        }
        else
        {
            // if there isn't currently a tip, but one is needed, only let it appear after a timeout
            if (newTip.isNotEmpty()
                && newTip != tipShowing
                && now > lastCompChangeTime + (juce::uint32)millisecondsBeforeTipAppears)
            {
                showTip();
            }
        }
    }
}



//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="RangeDisplay" componentName=""
                 parentClasses="public juce::Component" constructorParams="" variableInitialisers=""
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="600" initialHeight="400">
  <BACKGROUND backgroundColour="ff323e44"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

