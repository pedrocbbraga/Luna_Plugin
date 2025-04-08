/*
  ==============================================================================

    DistSliderA.h
    Created: 26 Feb 2025 6:56:04pm
    Author:  Pedro Cajaty B. Braga

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include"DistSliderAStyle.h"

class DistSliderA : public juce::Component, public juce::Slider::Listener
{
public:
    DistSliderA();
    ~DistSliderA() override;
    juce::Slider slider;

    
//    void paint (juce::Graphics&) override;
    void resized() override;
    void sliderValueChanged (juce::Slider* slider) override;
    
private:
    DistLNF_A distLNF;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DistSliderA)
};
