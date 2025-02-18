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

void MoonSlider::paint(juce::Graphics& g)
{
    loadMoonTexture();
}

void MoonSlider::loadMoonTexture()
{
    // Load the moon image from the JUCE resources
    auto moonImage = juce::ImageCache::getFromMemory(BinaryData::bright_moon_png, BinaryData::bright_moon_pngSize);
    
    if (! moonImage.isNull())
    {
        moonImageComponent.setImage (moonImage, juce::RectanglePlacement::stretchToFit);
    }
    else
    {
        DBG("ERROR: Moon image failed to load");
        jassertfalse;
    }
}
