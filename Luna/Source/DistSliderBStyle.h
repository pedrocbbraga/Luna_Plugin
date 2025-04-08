/*
  ==============================================================================

    DistSliderBStyle.h
    Created: 8 Apr 2025 3:39:45pm
    Author:  Pedro Cajaty B. Braga

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class DistLNF_B : public juce::LookAndFeel_V4
{
public:
    DistLNF_B();
    ~DistLNF_B() override;

    void drawLinearSlider(juce::Graphics& g, int x, int y, int width, int height, float sliderPos, float minSliderPos, float maxSliderPos, const juce::Slider::SliderStyle, juce::Slider& slider) override;

private:
//    juce::Image moonImage;
//    juce::Image blackCircle;
//    juce::Path ellipsePath;
};
