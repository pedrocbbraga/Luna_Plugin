/*
  ==============================================================================

    GraphicsVisualizer.h
    Created: 28 Apr 2025 10:51:24am
    Author:  Pedro Cajaty B. Braga

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

class GraphicsVisualizer : public juce::AnimatedAppComponent
{
public:
    //==============================================================================
    //MainComponent();
    GraphicsVisualizer(LunaAudioProcessor& processor, std::function<const juce::AudioBuffer<float>&()> bufferGetter, juce::Colour color);
    ~GraphicsVisualizer();

    //==============================================================================
    void update() override;

    //==============================================================================
    void paint (juce::Graphics& g) override;
    void resized() override;
    void addNewSample (float newSample, int sampleAmt);
    
private:
    //==============================================================================
    std::function<const juce::AudioBuffer<float>&()> bufferGetter;
    juce::Colour graphicsColor;
    
    LunaAudioProcessor& processor;
    
    juce::OpenGLContext openGLContext; // The instance to use OpenGL
    
    // Animation Variables =====================================================
    float centeredXPosition { 0.0f };
    static constexpr int PARTS = 1024;
    std::vector<float> partsHeight;
    
    static constexpr float INCREMENT { 0.01f }; //Original: 2.0f
    static constexpr float PART_OFFSET { 0.01f };
    bool isForward { true };


    float getPartDistanceOffset (int partIndexOffset)
    {
        return centeredXPosition + partIndexOffset * PART_OFFSET;
    }
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GraphicsVisualizer)
};

