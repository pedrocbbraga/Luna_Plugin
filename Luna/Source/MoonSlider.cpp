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
    setRange(0.0,100, 0);
    setSliderStyle(juce::Slider::LinearHorizontal);
    
    setSize (800, 800);
    loadMoonImage();
    loadBlackImage();
    
    setSliderSnapsToMousePosition(true);
    
    addListener(this);
}

MoonSlider::~MoonSlider()
{
    //Clean up
}

void MoonSlider::paint(juce::Graphics& g)
{
    Slider::paint (g);
    
    g.drawImageWithin(moonImage, 0, 0, getWidth(), getHeight(), juce::RectanglePlacement::stretchToFit);
    
    g.setColour (juce::Colour {0xFF2A2A2A});
    g.drawEllipse(25, 25, 190, 190, 7);
    
    // Ellipse for clipping mask
    ellipsePath.addEllipse(25, 21, 195, 195);
    
    float sliderValue = getValue();
    printf("slider value: %f\n", sliderValue);
    printf("slider style: %u\n", getSliderStyle());
    printf("interval: %lf\n", getInterval());
    
    g.reduceClipRegion(ellipsePath);
    g.drawImageWithin(blackCircle, sliderValue * 2, -16, getWidth() + 30, getHeight() + 30, juce::RectanglePlacement::stretchToFit);
}

void MoonSlider::resized()
{
}

void MoonSlider::sliderValueChanged (juce::Slider* slider)
{
    if (slider == this)
    {
        repaint();
    }
}

void MoonSlider::loadMoonImage()
{
    moonImage = juce::ImageCache::getFromMemory(BinaryData::whiteMoon_png, BinaryData::whiteMoon_pngSize);
    
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

void MoonSlider::loadBlackImage()
{
    blackCircle = juce::ImageCache::getFromMemory(BinaryData::blackCircle_png, BinaryData::blackCircle_pngSize);
    
    if (! moonImage.isNull())
    {
        blackCircleComponent.setImage (moonImage, juce::RectanglePlacement::stretchToFit);
    }
    else
    {
        DBG("ERROR: Moon image failed to load");
        jassertfalse;
    }
}


