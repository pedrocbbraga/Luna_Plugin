/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent   : public juce::AnimatedAppComponent
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent();

    //==============================================================================
    void update() override;

    //==============================================================================
    void paint (juce::Graphics& g) override;
    void resized() override;

private:
    //==============================================================================
    juce::OpenGLContext openGLContext; // The instance to use OpenGL
    
    // Animation Variables =====================================================
    float centeredXPosition { 0.0f };
    static constexpr int PARTS = 18;
    std::vector<float> partsHeight;
    
    static constexpr float INCREMENT { 2.0f };
    static constexpr float PART_OFFSET { 50.0f };
    bool isForward { true };


    float getPartDistanceOffset (int partIndexOffset)
    {
        return centeredXPosition + partIndexOffset * PART_OFFSET;
    }
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
