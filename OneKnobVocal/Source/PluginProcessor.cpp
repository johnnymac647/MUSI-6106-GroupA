/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "Compressor.h"
#include "DeEsser.h"
#include "Equalizer.h"
#include "Gate.h"
#include "Reverb.h"
#include "Saturator.h"


//==============================================================================
OneKnobVocalAudioProcessor::OneKnobVocalAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ), mainProcessor(new juce::AudioProcessorGraph()),
    apvts{ *this, nullptr, "Parameters", createParameterLayout() }
#endif
{
    Gate::addToKnobMap(knobValueMap);
    Deesser::addToKnobMap(knobValueMap);
    Equalizer::addToKnobMap(knobValueMap);
    Compressor::addToKnobMap(knobValueMap);
    Saturator::addToKnobMap(knobValueMap);
    Reverb::addToKnobMap(knobValueMap);

    juce::HashMap<juce::String, ModdedNormalisableRange<double>>::Iterator i(knobValueMap);
    while (i.next())
    {
        mappingRangeFlip.set(i.getKey(), false);
    }

    apvts.addParameterListener("ONE_KNOB", this);

    // Alison: Merge John's GUI
    // Make sure you set the size of the component after
    // you add any child components.
//     setSize (800, 600);

//     // Some platforms require permissions to open input channels so request that here
//     if (juce::RuntimePermissions::isRequired (juce::RuntimePermissions::recordAudio)
//         && ! juce::RuntimePermissions::isGranted (juce::RuntimePermissions::recordAudio))
//     {
//         juce::RuntimePermissions::request (juce::RuntimePermissions::recordAudio,
//                                            [&] (bool granted) { setAudioChannels (granted ? 2 : 0, 2); });
//     }
//     else
//     {
//         // Specify the number of input and output channels that we want to open
//         setAudioChannels (2, 2);
//     }
    
    
//     addAndMakeVisible(knob);
//     knob.setSliderStyle(juce::Slider::Rotary);
//     knob.setTextBoxStyle(juce::Slider::NoTextBox, true, 50, 10);
//     knob.setRange(0, 100);
//     knob.addListener(this);
    
//     addAndMakeVisible(knobLabel);
// //    knobLabel.setText("Value", juce::dontSendNotification);
//     knobLabel.attachToComponent(&knob, true);
    
//     royalTheme.setColour(juce::Slider::thumbColourId, textColor);
//     royalTheme.setColour(juce::Slider::textBoxTextColourId, textColor);
//     royalTheme.setColour(juce::Slider::rotarySliderFillColourId, textColor);
//     royalTheme.setColour(juce::Slider::rotarySliderOutlineColourId, darkGold);
//     royalTheme.setColour(juce::Slider::textBoxOutlineColourId, clear);
    
//     knob.setLookAndFeel(&royalTheme);

}

OneKnobVocalAudioProcessor::~OneKnobVocalAudioProcessor()
{
}

//==============================================================================
const juce::String OneKnobVocalAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool OneKnobVocalAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool OneKnobVocalAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool OneKnobVocalAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double OneKnobVocalAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int OneKnobVocalAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int OneKnobVocalAudioProcessor::getCurrentProgram()
{
    return 0;
}

void OneKnobVocalAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String OneKnobVocalAudioProcessor::getProgramName (int index)
{
    return {};
}

void OneKnobVocalAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void OneKnobVocalAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    mainProcessor->setPlayConfigDetails(getMainBusNumInputChannels(),
        getMainBusNumOutputChannels(),
        sampleRate, samplesPerBlock);

    mainProcessor->prepareToPlay(sampleRate, samplesPerBlock);

    initialiseGraph();

    for (auto node : mainProcessor->getNodes())
    {
        node->getProcessor()->setPlayConfigDetails(getMainBusNumInputChannels(),
            getMainBusNumOutputChannels(),
            sampleRate, samplesPerBlock);
        node->getProcessor()->prepareToPlay(sampleRate, samplesPerBlock);
        node->getProcessor()->enableAllBuses();
    }
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    
    mRmsInputLeft.reset(sampleRate, 0.5); //smooth the value when it goes down
    mRmsInputRight.reset(sampleRate, 0.5);
    mRmsOutputLeft.reset(sampleRate, 0.5);
    mRmsOutputRight.reset(sampleRate, 0.5);
    
    mRmsInputLeft.setCurrentAndTargetValue(-100.f); //set the initial value
    mRmsInputRight.setCurrentAndTargetValue(-100.f);;
    mRmsOutputLeft.setCurrentAndTargetValue(-100.f);;
    mRmsOutputRight.setCurrentAndTargetValue(-100.f);;
}

void OneKnobVocalAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

//==============================================================================
// Alison: Merge John's GUI
// void OneKnobVocalAudioProcessor::paint (juce::Graphics& g)
// {
//     // (Our component is opaque, so we must completely fill the background with a solid colour)
//     //g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

//     g.fillAll(backgroundColor);
//     g.setColour(textColor);
//     g.drawText("Voce Dolce", getWidth()/2 - 100, 50, 200, 20, juce::Justification::centred, true);
    
//     g.setColour(lightPurple);
//     g.fillRect(getWidth() - 10 - 50 , 10, 50, 50);
//     g.drawImageAt (gear, getWidth() - 60, 10);
// //    g.drawText(s_knobValue);
    
// }

// void OneKnobVocalAudioProcessor::resized()
// {
//     // This is called when the MainContentComponent is resized.
//     // If you add any child components, this is where you should
//     // update their positions.
//     auto sliderWidth = 300;
//     knob.setBounds ((getWidth() - sliderWidth)/2 - 10, (getHeight() - sliderWidth)/2, sliderWidth, sliderWidth);
// }

// void OneKnobVocalAudioProcessor::sliderValueChanged(juce::Slider *slider){
//     if(slider == &knob){
//         s_knobValue = juce::String( knob.getValue() );
// //        g.drawText(s_knobValue, getBounds())
//     }
// }
//==============================================================================


#ifndef JucePlugin_PreferredChannelConfigurations
bool OneKnobVocalAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void OneKnobVocalAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.

    
    
    /*
    calculate the RMS of the block size.
    The time resolution depends on the block size of the host, but it's acceptable.
     */
    
    // the next smoothed value is after the length of the processing block
    mRmsInputLeft.skip(buffer.getNumSamples());
    mRmsInputRight.skip(buffer.getNumSamples());
    mRmsOutputLeft.skip(buffer.getNumSamples());
    mRmsOutputRight.skip(buffer.getNumSamples());
    
    float rmsInputLeft = juce::Decibels::gainToDecibels(buffer.getRMSLevel(0, 0, buffer.getNumSamples()));
    if (rmsInputLeft < mRmsInputLeft.getCurrentValue())
        mRmsInputLeft.setTargetValue(rmsInputLeft); //smooth the value only when it goes down
    else
        mRmsInputLeft.setCurrentAndTargetValue(rmsInputLeft);
    
    float rmsInputRight = juce::Decibels::gainToDecibels(buffer.getRMSLevel(1, 0, buffer.getNumSamples()));
    if (rmsInputRight < mRmsInputRight.getCurrentValue())
        mRmsInputRight.setTargetValue(rmsInputRight); //smooth the value only when it goes down
    else
        mRmsInputRight.setCurrentAndTargetValue(rmsInputRight);
    
    
    //all the audio processing
    mainProcessor->processBlock(buffer, midiMessages);
    

    
    float rmsOutputLeft = juce::Decibels::gainToDecibels(buffer.getRMSLevel(0, 0, buffer.getNumSamples()));
    if (rmsOutputLeft < mRmsOutputLeft.getCurrentValue())
        mRmsOutputLeft.setTargetValue(rmsOutputLeft); //smooth the value only when it goes down
    else
        mRmsOutputLeft.setCurrentAndTargetValue(rmsOutputLeft);
    
    
    float rmsOutputRight = juce::Decibels::gainToDecibels(buffer.getRMSLevel(1, 0, buffer.getNumSamples()));
    if (rmsOutputRight < mRmsOutputRight.getCurrentValue())
        mRmsOutputRight.setTargetValue(rmsOutputRight); //smooth the value only when it goes down
    else
        mRmsOutputRight.setCurrentAndTargetValue(rmsOutputRight);
    
    
    
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);

        // ..do something to the data...
    }
}

//==============================================================================
bool OneKnobVocalAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* OneKnobVocalAudioProcessor::createEditor()
{
    return new OneKnobVocalAudioProcessorEditor (*this);
}

//==============================================================================
void OneKnobVocalAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    auto paramsValueTree = apvts.copyState();
    auto mappingValueTree = saveMapToValueTree();
    juce::ValueTree state("SavingState");
    state.addChild(paramsValueTree, -1, nullptr);
    state.addChild(mappingValueTree, -1, nullptr);
    std::unique_ptr<juce::XmlElement> xml(state.createXml());
    copyXmlToBinary(*xml, destData);
}

void OneKnobVocalAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    std::unique_ptr<juce::XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));

    if (xmlState.get() != nullptr)
    {
        auto state = juce::ValueTree::fromXml(*xmlState);

        loadMapFromValueTree(state);
        if (state.getChildWithName(apvts.state.getType()).isValid())
            apvts.replaceState(state.getChildWithName(apvts.state.getType()));
    }

}



float OneKnobVocalAudioProcessor::getRmsValue(const int channel, const int position) const
{
    jassert(channel == 0 || channel == 1); //only accept stereo
    jassert(position == 0 || position == 1); //only two position: intput (0) and output (1)
    
    
    if (channel == 0)
    {
        if(position == 0)
            return mRmsInputLeft.getCurrentValue();
        else if (position == 1)
            return mRmsOutputLeft.getCurrentValue();
    }
    
    if (channel == 1)
    {
        if(position == 0)
            return mRmsInputRight.getCurrentValue();
        else if (position == 1)
            return mRmsOutputRight.getCurrentValue();
    }
    
    return 0.f;

}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new OneKnobVocalAudioProcessor();
}

void OneKnobVocalAudioProcessor::initialiseAudioNodes(juce::ReferenceCountedArray<juce::AudioProcessorGraph::Node>& audioNodeList) //TODO: Could someone make this neat?
{ 

    gateNode = mainProcessor->addNode(std::make_unique<Gate>(&apvts));
    audioNodeList.add(gateNode);

    deEsserNode = mainProcessor->addNode(std::make_unique<Deesser>(&apvts));
    audioNodeList.add(deEsserNode);

    equalizerNode = mainProcessor->addNode(std::make_unique<Equalizer>(&apvts));
    audioNodeList.add(equalizerNode);

    compressorNode = mainProcessor->addNode(std::make_unique<Compressor>(&apvts));
    audioNodeList.add(compressorNode);

    saturatorNode = mainProcessor->addNode(std::make_unique<Saturator>(&apvts));
    audioNodeList.add(saturatorNode);

    reverbNode = mainProcessor->addNode(std::make_unique<Reverb>(&apvts));
    audioNodeList.add(reverbNode);

}

void OneKnobVocalAudioProcessor::connectAudioNodes(juce::ReferenceCountedArray<juce::AudioProcessorGraph::Node>& audioNodeList)

{
    for (int i = 0; i < audioNodeList.size() - 1; ++i)
    {
        for (int channel = 0; channel < 2; ++channel)
            mainProcessor->addConnection({ { audioNodeList.getUnchecked(i)->nodeID,      channel },
                                            { audioNodeList.getUnchecked(i + 1)->nodeID,  channel } });
    }
    for (int channel = 0; channel < 2; ++channel)
    {
        mainProcessor->addConnection({ { audioInputNode->nodeID,  channel },
                                        { audioNodeList.getFirst()->nodeID, channel } });
        mainProcessor->addConnection({ { audioNodeList.getLast()->nodeID,  channel },
                                        { audioOutputNode->nodeID, channel } });
    }
}

void OneKnobVocalAudioProcessor::connectMidiNodes()
{
    mainProcessor->addConnection({ { midiInputNode->nodeID,  juce::AudioProcessorGraph::midiChannelIndex },
                                    { midiOutputNode->nodeID, juce::AudioProcessorGraph::midiChannelIndex } });
}


void OneKnobVocalAudioProcessor::initialiseGraph()
{

    juce::ReferenceCountedArray<juce::AudioProcessorGraph::Node> audioNodeList;

    mainProcessor->clear();

    audioInputNode = mainProcessor->addNode(std::make_unique<juce::AudioProcessorGraph::AudioGraphIOProcessor>(juce::AudioProcessorGraph::AudioGraphIOProcessor::audioInputNode));
    audioOutputNode = mainProcessor->addNode(std::make_unique<juce::AudioProcessorGraph::AudioGraphIOProcessor>(juce::AudioProcessorGraph::AudioGraphIOProcessor::audioOutputNode));
   
    
    midiInputNode = mainProcessor->addNode(std::make_unique<juce::AudioProcessorGraph::AudioGraphIOProcessor>(juce::AudioProcessorGraph::AudioGraphIOProcessor::midiInputNode));
    midiOutputNode = mainProcessor->addNode(std::make_unique<juce::AudioProcessorGraph::AudioGraphIOProcessor>(juce::AudioProcessorGraph::AudioGraphIOProcessor::midiOutputNode));

    initialiseAudioNodes(audioNodeList);
    connectAudioNodes(audioNodeList);
    connectMidiNodes();
}

juce::AudioProcessorValueTreeState::ParameterLayout OneKnobVocalAudioProcessor::createParameterLayout()
{
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;

    Gate::addToParameterLayout(params);
    Deesser::addToParameterLayout(params);
    Equalizer::addToParameterLayout(params);
    Compressor::addToParameterLayout(params);
    Saturator::addToParameterLayout(params);
    Reverb::addToParameterLayout(params);

    params.push_back(std::make_unique<juce::AudioParameterFloat>("ONE_KNOB", "OneKnob", 0.0f, 1.0f, 0.5f));

    return { params.begin() , params.end() };
}
