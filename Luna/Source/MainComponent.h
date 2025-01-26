/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent : public juce::AnimatedAppComponent
{
public:
    //==============================================================================
    //MainComponent();
    MainComponent(LunaAudioProcessor& processor);
    ~MainComponent();

    //==============================================================================
    void update() override;

    //==============================================================================
    void paint (juce::Graphics& g) override;
    void resized() override;
    void addNewSample (float newSample, int sampleAmt);
    
private:
    //==============================================================================
    LunaAudioProcessor& processor;
    
    juce::OpenGLContext openGLContext; // The instance to use OpenGL
    
    // Animation Variables =====================================================
    float centeredXPosition { 0.0f };
    static constexpr int PARTS = 1024;
    std::vector<float> partsHeight;
    
    static constexpr float INCREMENT { 0.1f }; //Original: 2.0f
    static constexpr float PART_OFFSET { 0.1f };
    bool isForward { true };


    float getPartDistanceOffset (int partIndexOffset)
    {
        return centeredXPosition + partIndexOffset * PART_OFFSET;
    }
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
