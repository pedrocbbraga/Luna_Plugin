/*
  ==============================================================================

    MoonSlider.cpp
    Created: 5 Feb 2025 5:59:14pm
    Author:  Pedro Cajaty B. Braga

  ==============================================================================
*/

#include "MoonSlider.h"

MoonSlider::MoonSlider()
{
    setRange(0.0, 1.0, 0.01);
    setSliderStyle(juce::Slider::LinearHorizontal);
}

MoonSlider::~MoonSlider() {}

void MoonSlider::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::black);
    g.setColour(juce::Colours::white);
    
    // Draw placeholder moon (this will be replaced by OpenGL)
    float diameter = getHeight() * 0.8f;
    float x = (getWidth() - diameter) / 2;
    float y = (getHeight() - diameter) / 2;
    g.fillEllipse(x, y, diameter, diameter);
}

void MoonSlider::resized()
{
    // Called when the slider is resized (useful for OpenGL later)
}
