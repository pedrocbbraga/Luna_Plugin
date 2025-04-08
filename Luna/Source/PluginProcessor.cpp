/*fart*/
#include "PluginProcessor.h"
#include "PluginEditor.h"
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
    
    auto delayBufferSize = 1024 ;
    delayBuffer.setSize(getTotalNumOutputChannels(), (int)delayBufferSize) ;
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

//=PROCESS BLOCK=======================================================================================
void LunaAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    
    auto bufferSize = buffer.getNumSamples() ;
    auto delayBufferSize = delayBuffer.getNumSamples() ;
    
    //float dbGain = *treeState.getRawParameterValue("gain") ;
    //float rawGain = juce::Decibels::decibelsToGain(dbGain) ;
        
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);
        
        // Checks if main buffer can copy to delay buffer without needing to wrap
        if (delayBufferSize > bufferSize + writePosition)
        {
            // Copy main buffer contents to delay buffer
            delayBuffer.copyFromWithRamp(channel, writePosition, channelData, bufferSize, 0.1f, 0.1f) ;
        }
        else
        {
            // Determine how much space is left at the end of the delay buffer
            auto numSamplesToEnd = delayBufferSize - writePosition ;
            
            // Copy that number of contents to the end
            delayBuffer.copyFromWithRamp(channel, writePosition, channelData, numSamplesToEnd, 0.1f, 0.1f) ;
            
            // Determine how much contents is remaining to copy
            auto numSamplesAtStart = bufferSize - numSamplesToEnd ;
            
            // Copy remaining amount to beginning of delay buffer
            delayBuffer.copyFromWithRamp(channel, 0, channelData + numSamplesToEnd, numSamplesAtStart, 0.1f, 0.1f) ;
            
        }
        
        for (int sample = 0; sample < buffer.getNumSamples(); sample++)
        {
        
            //channelData[sample] = (2.f / juce::MathConstants<float>::pi) * atan(distOnSlider * channelData[sample]) ;
            
            if (channelData[sample] != 0)
            {
                //channelData[sample] = std::tanh(3.0f * channelData[sample]) / std::tanh(channelData[sample]) ;
                if (channelData[sample] > 0)
                {
                    dist_sample_value = sqrt( ( ( 1 + pow(a, 2) ) * sin(channelData[sample]) ) / ( 1 + pow(a, 2) * pow(sin(channelData[sample]), 2) ) ) ;
                }
                if (channelData[sample] < 0)
                {
                    dist_sample_value = - sqrt( ( ( 1 + pow(b, 2) ) * fabs( sin(channelData[sample]) ) ) / ( 1 + pow(b, 2) * pow(sin(channelData[sample]), 2) ) ) ;
                }
            }
            
            channelData[sample] = channelData[sample]*(1-dw) + dist_sample_value*dw;
            
            channelData[sample] *= 0.3f ;
            
        }
        
    }
    
    
//    TESTING DELAY BUFFER WRAP AROUND
//    DBG ("Delay Buffer Size: " << delayBufferSize);
//    DBG ("Buffer Size: " << bufferSize);
//    DBG ("Write Position: " << writePosition);
    
    writePosition += bufferSize ;
    writePosition %= delayBufferSize ;
    
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
