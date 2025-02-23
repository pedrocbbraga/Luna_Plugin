/*
  ==============================================================================

    MoonSliderStyle.h
    Created: 21 Feb 2025 10:26:21am
    Author:  Pedro Cajaty B. Braga

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class MoonLNF : public juce::LookAndFeel_V4
{
public:
    MoonLNF();
    ~MoonLNF() override;

    void drawLinearSlider(juce::Graphics& g, int x, int y, int width, int height, float sliderPos, float minSliderPos, float maxSliderPos, const juce::Slider::SliderStyle, juce::Slider& slider) override;

private:
    juce::Image moonImage;
    juce::Image blackCircle;
    juce::Path ellipsePath;
};
