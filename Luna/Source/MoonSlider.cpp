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
//    DBG(slider.getValue());
    slider.setTextBoxStyle(juce::Slider::NoTextBox, true, 100, 25);
    
    slider.setLookAndFeel(&moonLNF);
    slider.addListener(this);
    addAndMakeVisible(slider);
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
//        DBG("repainted");
//        DBG(slider->getValue());
        repaint();
    }
}
