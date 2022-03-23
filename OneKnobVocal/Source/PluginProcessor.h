/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/**
*/
class OneKnobVocalAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    OneKnobVocalAudioProcessor();
    ~OneKnobVocalAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

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

    juce::AudioProcessorGraph::Node::Ptr inputGainNode;
    juce::AudioProcessorGraph::Node::Ptr gateNode;
    juce::AudioProcessorGraph::Node::Ptr deEsserNode;
    juce::AudioProcessorGraph::Node::Ptr equalizerNode;
    juce::AudioProcessorGraph::Node::Ptr compressorNode;
    juce::AudioProcessorGraph::Node::Ptr saturatorNode;
    juce::AudioProcessorGraph::Node::Ptr reverbNode;
    juce::AudioProcessorGraph::Node::Ptr outputGainNode;

    juce::AudioProcessorValueTreeState apvts;
    juce::HashMap<juce::String, juce::NormalisableRange<float>> knobValueMap;

private:
    juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout();

    std::unique_ptr<juce::AudioProcessorGraph> mainProcessor;
    void initialiseAudioNodes(juce::ReferenceCountedArray<juce::AudioProcessorGraph::Node>& audioNodeList);
    void connectAudioNodes(juce::ReferenceCountedArray<juce::AudioProcessorGraph::Node>& audioNodeList);
    void connectMidiNodes();
    void initialiseGraph();   
    
    juce::AudioProcessorGraph::Node::Ptr midiInputNode;
    juce::AudioProcessorGraph::Node::Ptr midiOutputNode;

    juce::AudioProcessorGraph::Node::Ptr audioInputNode;
    juce::AudioProcessorGraph::Node::Ptr audioOutputNode;


    juce::ValueTree saveMapToValueTree()
    {
        juce::ValueTree mapValueTree("Mappings");
        juce::HashMap<juce::String, juce::NormalisableRange<float>>::Iterator i(knobValueMap);
        while (i.next())
        {
            juce::ValueTree currentMappingValue("NormRange");
            currentMappingValue.setProperty("id", i.getKey(), nullptr);
            currentMappingValue.setProperty("Start", i.getValue().start, nullptr);
            currentMappingValue.setProperty("End", i.getValue().end, nullptr);
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
                    knobValueMap.set(range["id"].toString(), juce::NormalisableRange<float>(range["Start"], range["End"]));
                }
            }
        }
        if (apvts.getParameter("ONE_KNOB")->getValue() != 0)
            apvts.getParameter("ONE_KNOB")->setValueNotifyingHost(0);
        else
            apvts.getParameter("ONE_KNOB")->setValueNotifyingHost(0.01);
    }

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OneKnobVocalAudioProcessor)
};
 