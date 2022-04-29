/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "ModdedNormalisableRange.h"


//==============================================================================
/**
*/
class OneKnobVocalAudioProcessor  : public juce::AudioProcessor,
    juce::AudioProcessorValueTreeState::Listener
{
public:
    //==============================================================================
    OneKnobVocalAudioProcessor();
    ~OneKnobVocalAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

    //==============================================================================
    // Alison: Merge John's GUI
    // void paint (juce::Graphics& g) override;
    // void resized() override;
    // void sliderValueChanged (juce::Slider* slider) override;
    //==============================================================================

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    float getRmsValue(const int channel, const int position) const;

    void parameterChanged(const juce::String& parameterID, float newValue)
    {
        if (parameterID == "ONE_KNOB")
        {
            juce::HashMap<juce::String, ModdedNormalisableRange<double>>::Iterator i(knobValueMap);
            while (i.next())
            {
                if (mappingRangeFlip[i.getKey()])
                {
                    apvts.getParameter(i.getKey())->setValueNotifyingHost(apvts.getParameter(i.getKey())->convertTo0to1(i.getValue().convertFrom0to1(1 - newValue)));
                }
                else 
                {
                    apvts.getParameter(i.getKey())->setValueNotifyingHost(apvts.getParameter(i.getKey())->convertTo0to1(i.getValue().convertFrom0to1(newValue)));
                }
            }
        }
    }


    void setAudioParameters()
    {
        if (audioParameterValuesToLoad.isValid())
            apvts.replaceState(audioParameterValuesToLoad);
    }

    juce::AudioProcessorValueTreeState apvts;
    juce::HashMap<juce::String, ModdedNormalisableRange<double>> knobValueMap;
    juce::HashMap<juce::String, bool> mappingRangeFlip;
    juce::ValueTree audioParameterValuesToLoad;

    juce::ChangeBroadcaster loadedPreset;

    bool isEditorOpen = false;

private:
    //RMS level smoothing
    juce::LinearSmoothedValue<float> mRmsInputLeft, mRmsInputRight, mRmsOutputLeft, mRmsOutputRight;
    
    juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout();

    std::unique_ptr<juce::AudioProcessorGraph> mainProcessor;
    void initialiseAudioNodes();
    void connectAudioNodes();
    void connectMidiNodes();
    void initialiseGraph();
    void prepareGraphForPlaying();
    
    juce::AudioProcessorGraph::Node::Ptr midiInputNode;
    juce::AudioProcessorGraph::Node::Ptr midiOutputNode;

    juce::AudioProcessorGraph::Node::Ptr audioInputNode;
    juce::AudioProcessorGraph::Node::Ptr audioOutputNode;

    juce::AudioProcessorGraph::Node::Ptr gateNode;
    juce::AudioProcessorGraph::Node::Ptr deEsserNode;
    juce::AudioProcessorGraph::Node::Ptr equalizerNode;
    juce::AudioProcessorGraph::Node::Ptr compressorNode;
    juce::AudioProcessorGraph::Node::Ptr saturatorNode;
    juce::AudioProcessorGraph::Node::Ptr reverbNode;

    juce::ReferenceCountedArray<juce::AudioProcessorGraph::Node> audioNodeList;


    juce::ValueTree saveMapToValueTree()
    {
        juce::ValueTree mapValueTree("Mappings");
        juce::HashMap<juce::String, ModdedNormalisableRange<double>>::Iterator i(knobValueMap);
        while (i.next())
        {
            juce::ValueTree currentMappingValue("NormRange");
            currentMappingValue.setProperty("id", i.getKey(), nullptr);
            currentMappingValue.setProperty("Start", i.getValue().start, nullptr);
            currentMappingValue.setProperty("End", i.getValue().end, nullptr);
            currentMappingValue.setProperty("Flip", mappingRangeFlip[i.getKey()], nullptr);
            mapValueTree.addChild(currentMappingValue.createCopy(), -1, nullptr);
        }
        return mapValueTree.createCopy();
    }

    void loadMapFromValueTree(juce::ValueTree state)
    {
        if (state.getChildWithName("Mappings").isValid())
        {
            for (auto range : state.getChildWithName("Mappings"))
            {
                if (range.hasType("NormRange"))
                {
                    knobValueMap.set(range["id"].toString(), ModdedNormalisableRange<double>(range["Start"], range["End"]));
                    mappingRangeFlip.set(range["id"].toString(), range["Flip"]);
                }
            }
        }
        loadedPreset.sendChangeMessage();
    }

    // Alison: Merging John's GUI
    //==============================================================================
    // juce::LookAndFeel_V4 royalTheme;    
    // juce::Colour backgroundColor = juce::Colour(0xff0f0038); //dark purple
    // juce::Colour textColor = juce::Colour(0xffc2b948); // gold
    // juce::Colour darkGold = juce::Colour(0xff423E12);
    // juce::Colour lightPurple = juce::Colour(0xff6B43E0);
    // juce::Colour clear = juce::Colour(0x00000000);
    
    // juce::Slider knob;
    // juce::Label knobLabel;
    
    // juce::String s_knobValue;
    
    // juce::Image gear;
    //==============================================================================

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OneKnobVocalAudioProcessor)
};
 
