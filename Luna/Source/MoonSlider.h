/*
  ==============================================================================

    MoonSlider.h
    Created: 5 Feb 2025 5:59:03pm
    Author:  Pedro Cajaty B. Braga

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class MoonSlider : public juce::Slider
{
public:
    MoonSlider();
    ~MoonSlider() override;

    void paint(juce::Graphics& g) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MoonSlider)
};
