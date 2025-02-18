#pragma once

#include <JuceHeader.h>

/*
  ==============================================================================

    MoonSlider.h
    Created: 12 Feb 2025 7:23:59pm
    Author:  Pedro Cajaty B. Braga

  ==============================================================================
*/

class MoonSlider : public juce::Slider
{
public:
    MoonSlider();
    ~MoonSlider() override;
    
    void paint (juce::Graphics&) override;
    void resized() override;
    
private:

    juce::Image moonImage;
    void loadMoonImage();
    
    juce::ImageComponent moonImageComponent;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MoonSlider)
};


