/*
  ==============================================================================

    MoonSlider.cpp
    Created: 12 Feb 2025 7:23:51pm
    Author:  Pedro Cajaty B. Braga

  ==============================================================================
*/

#include "MoonSlider.h"

MoonSlider::MoonSlider()
{
    setRange(0.0, 100.0, 0.1);
    setSliderStyle(juce::Slider::LinearHorizontal);
}

MoonSlider::~MoonSlider()
{
    //Clean up
}

void MoonSlider::paint(<#juce::Graphics &#>)
{
    
}
