/*
  ==============================================================================

    MoonSlider.cpp
    Created: 12 Feb 2025 7:23:51pm
    Author:  Pedro Cajaty B. Braga

  ==============================================================================
*/

#include "MoonSlider.h"
#include "MoonSliderStyle.h"

MoonSlider::MoonSlider()
{
    slider.setSliderStyle(juce::Slider::LinearHorizontal);
    slider.setRange(0.0, 100.0, 0.1);
    slider.setValue(50.0);
    slider.setTextBoxStyle(juce::Slider::NoTextBox, true, 100, 25);
    
    slider.setLookAndFeel(&moonLNF);
    slider.addListener(this);
    addAndMakeVisible(slider);
    
//    setLookAndFeel(&moonLNF);
//    setSize (800, 800);
    
//    loadMoonImage();
//    loadBlackImage();
//
}

MoonSlider::~MoonSlider()
{
    // Clean up
    slider.setLookAndFeel(nullptr);
}

void MoonSlider::resized()
{
    slider.setBounds(getLocalBounds());
}

void MoonSlider::sliderValueChanged (juce::Slider* slider)
{
    // Checks if slider that was changed is this class state's slider
    if (slider == &this->slider)
    {
        DBG("repainted");
        repaint();
    }
}

//void MoonSlider::paint(juce::Graphics& g)
//{
//    
////    g.drawImageWithin(moonImage, 0, 0, getWidth(), getHeight(), juce::RectanglePlacement::stretchToFit);
////    
////    g.setColour (juce::Colour {0xFF2A2A2A});
////    g.drawEllipse(25, 25, 190, 190, 7);
////    
////    // Ellipse for clipping mask
////    ellipsePath.addEllipse(25, 21, 195, 195);
////    
////    float sliderValue = slider.getValue();
//////    printf("slider value: %f\n", sliderValue);
//////    printf("slider style: %u\n", getSliderStyle());
//////    printf("interval: %lf\n", getInterval());
////    
////    g.reduceClipRegion(ellipsePath);
////    g.drawImageWithin(blackCircle, sliderValue * 2, -16, getWidth() + 30, getHeight() + 30, juce::RectanglePlacement::stretchToFit);
//}

//void MoonSlider::sliderValueChanged (juce::Slider* slider)
//{
//    if (slider == this)
//    {
//        repaint();
//    }
//}
//
//void MoonSlider::loadMoonImage()
//{
//    moonImage = juce::ImageCache::getFromMemory(BinaryData::whiteMoon_png, BinaryData::whiteMoon_pngSize);
//    
//    if (! moonImage.isNull())
//    {
//        moonImageComponent.setImage (moonImage, juce::RectanglePlacement::stretchToFit);
//    }
//    else
//    {
//        DBG("ERROR: Moon image failed to load");
//        jassertfalse;
//    }
//}
//
//void MoonSlider::loadBlackImage()
//{
//    blackCircle = juce::ImageCache::getFromMemory(BinaryData::blackCircle_png, BinaryData::blackCircle_pngSize);
//    
//    if (! moonImage.isNull())
//    {
//        blackCircleComponent.setImage (moonImage, juce::RectanglePlacement::stretchToFit);
//    }
//    else
//    {
//        DBG("ERROR: Moon image failed to load");
//        jassertfalse;
//    }
//}


