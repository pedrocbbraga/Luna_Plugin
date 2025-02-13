/*
  ==============================================================================

    MoonSlider.h
    Created: 12 Feb 2025 7:23:59pm
    Author:  Pedro Cajaty B. Braga

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/**
*/
class MoonSlider  : public juce::Slider
{
public:
    MoonSlider(juce:Slider);
    ~MoonSlider() override;
    
    void paint (juce::Graphics&) override;
    void resized() override;
    
private:
    
}
