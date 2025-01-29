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
class LunaAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    LunaAudioProcessor();
    ~LunaAudioProcessor() override;

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

    //** Value Trees =========================================================*/
    juce::AudioProcessorValueTreeState treeState;
    
    float a;
    float b;
    
    const juce::AudioBuffer<float>& getDelayBuffer() const { return delayBuffer; }
    
    const juce::AudioBuffer<float>& getVisualBuffer() const { return visualBuffer; }
    juce::AbstractFifo& getFifo() { return fifo; }
    //Getter for the private fifo and visualBuffer variables
    
private:
    
    juce::AudioBuffer<float> delayBuffer ;
    int writePosition { 0 } ;
    
    //** PARAMETERS =========================================================*/
    juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout() ;
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LunaAudioProcessor)
    
    juce::AudioBuffer<float> visualBuffer; // Buffer for visualization
    juce::AbstractFifo fifo { 512 };     // FIFO with a fixed size of 512 samples
    
};
