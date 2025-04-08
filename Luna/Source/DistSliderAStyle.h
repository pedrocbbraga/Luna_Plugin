/*
  ==============================================================================

    DistSliderAStyle.h
    Created: 26 Feb 2025 6:56:37pm
    Author:  Pedro Cajaty B. Braga

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class DistLNF_A : public juce::LookAndFeel_V4
{
public:
    DistLNF_A();
    ~DistLNF_A() override;

    void drawLinearSlider(juce::Graphics& g, int x, int y, int width, int height, float sliderPos, float minSliderPos, float maxSliderPos, const juce::Slider::SliderStyle, juce::Slider& slider) override;

private:
//    juce::Image moonImage;
//    juce::Image blackCircle;
//    juce::Path ellipsePath;
};
