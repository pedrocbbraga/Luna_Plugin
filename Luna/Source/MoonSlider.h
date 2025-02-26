#pragma once

#include <JuceHeader.h>
#include "MoonSliderStyle.h"

/*
  ==============================================================================

    MoonSlider.h
    Created: 12 Feb 2025 7:23:59pm
    Author:  Pedro Cajaty B. Braga

  ==============================================================================
*/

class MoonSlider : public juce::Component, public juce::Slider::Listener
{
public:
    MoonSlider();
    ~MoonSlider() override;
    juce::Slider slider;

    
//    void paint (juce::Graphics&) override;
    void resized() override;
    void sliderValueChanged (juce::Slider* slider) override;
    
private:
    MoonLNF moonLNF;
    
    
//    juce::Image moonImage;
//    juce::ImageComponent moonImageComponent;
//    
//    juce::Image blackCircle;
//    juce::ImageComponent blackCircleComponent;
//    
//    juce::Path ellipsePath;
//    
//    void loadMoonImage();
//    void loadBlackImage();
//    
//    void sliderValueChanged (juce::Slider* slider) override ;
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MoonSlider)
};


