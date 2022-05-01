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
    void savePluginPreset(juce::MemoryBlock& destData);
    void setStateInformation (const void* data, int sizeInBytes) override;

    void loadSavedPreset(const void* data, int sizeInBytes);
    
    float getRmsValue(const int channel, const int position) const;

    void setAudioParameters();

    juce::AudioProcessorValueTreeState apvts;
    juce::HashMap<juce::String, ModdedNormalisableRange<double>> knobValueMap;
    juce::HashMap<juce::String, bool> mappingRangeFlip;
    juce::ValueTree audioParameterValuesToLoad;

    int selectedComboBoxID = 1;

    juce::String selectedComboBoxMessage = "Custom";


    juce::ChangeBroadcaster loadedStateInformation;

    juce::ChangeBroadcaster loadedPreset;

    juce::ChangeBroadcaster loadedApvts;

    bool isEditorInAdvancedMode = false;

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


    juce::ValueTree saveMapToValueTree();

    void loadMapFromValueTree(juce::ValueTree state);

    void parameterChanged(const juce::String& parameterID, float newValue) override;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OneKnobVocalAudioProcessor)
};
 
