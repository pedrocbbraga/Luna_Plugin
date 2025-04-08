/*
  ==============================================================================

    DistSliderB.h
    Created: 8 Apr 2025 3:39:54pm
    Author:  Pedro Cajaty B. Braga

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include"DistSliderBStyle.h"

class DistSliderB : public juce::Component, public juce::Slider::Listener
{
public:
    DistSliderB();
    ~DistSliderB() override;
    juce::Slider slider;

    
//    void paint (juce::Graphics&) override;
    void resized() override;
    void sliderValueChanged (juce::Slider* slider) override;
    
private:
    DistLNF_B distLNF;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DistSliderB)
};
