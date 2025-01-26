/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/
/*fart*/
#include "PluginProcessor.h"
#include "PluginEditor.h"
//#include <juce_dsp/maths/juce_FastMathApproximations.h>
#include <cmath>

//==============================================================================
LunaAudioProcessor::LunaAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ), treeState(*this, nullptr, "PARAMETERS", createParameterLayout())
#endif
{
}

LunaAudioProcessor::~LunaAudioProcessor()
{
}

juce::AudioProcessorValueTreeState::ParameterLayout LunaAudioProcessor::createParameterLayout()
{
    std::vector <std::unique_ptr<juce::RangedAudioParameter>> params ;
    
    auto pGain = std::make_unique<juce::AudioParameterFloat>(juce::ParameterID {"gain", 1}, "Gain", -100.0, 12.0, 0.0) ;
    params.push_back(std::move(pGain)) ;
    
    auto pDist = std::make_unique<juce::AudioParameterFloat>(juce::ParameterID {"dist", 1}, "Dist", 0.0, 100.0, 0.0) ;
    params.push_back(std::move(pDist)) ;
    
    return { params.begin(), params.end() } ;
}

//==============================================================================
const juce::String LunaAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool LunaAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool LunaAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool LunaAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double LunaAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int LunaAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int LunaAudioProcessor::getCurrentProgram()
{
    return 0;
}

void LunaAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String LunaAudioProcessor::getProgramName (int index)
{
    return {};
}

void LunaAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void LunaAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void LunaAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool LunaAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void LunaAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    visualBuffer.setSize(totalNumInputChannels, buffer.getNumSamples());
    
    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    float frequency = 420.0f; // Frequency in Hz
    float amplitude = 1.0f;   // Signal amplitude
    static float phase = 0.0f;
    float phaseIncrement = (2.0f * juce::MathConstants<float>::pi * frequency) / getSampleRate();
    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    
    float dbGain = *treeState.getRawParameterValue("gain") ;
    float rawGain = juce::Decibels::decibelsToGain(dbGain) ;
    
    //float rawDist = *treeState.getRawParameterValue("dist") ;
        
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);
        const auto* inputChannelData = buffer.getReadPointer(channel);
        
        for (int sample = 0; sample < buffer.getNumSamples(); sample++)
        {
            //*channelData *= 15.0 ;
            //*channelData = (2.f / juce::  MathConstants<float>::pi) * atan(distOnSlider * *channelData) ;
            
//            channelData[sample] *= rawGain ;
            channelData[sample] = amplitude * std::sin(phase);
            phase += phaseIncrement;
            if (phase >= 2.0f * juce::MathConstants<float>::pi)
                            phase -= 2.0f * juce::MathConstants<float>::pi;
            
            // Soft Diode Clipping Function Test
            //*channelData = std::tanh(2.0f * *channelData) / std::tanh(*channelData) ;
            //*channelData *= 0.3 ;
            
            //channelData++;
        }
//        auto* visualChannelData = buffer.getReadPointer(channel);

        int start1, size1, start2, size2;
        fifo.prepareToWrite(buffer.getNumSamples(), start1, size1, start2, size2);

        if (size1 > 0)
            visualBuffer.copyFrom(channel, start1, inputChannelData, size1);

        if (size2 > 0)
            visualBuffer.copyFrom(channel, start2, inputChannelData + size1, size2);

        fifo.finishedWrite(size1 + size2);
    }
    
}

//==============================================================================
bool LunaAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* LunaAudioProcessor::createEditor()
{
    return new LunaAudioProcessorEditor (*this);
    
    //return new juce::GenericAudioProcessorEditor(*this) ;
}

//==============================================================================
void LunaAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void LunaAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new LunaAudioProcessor();
}
