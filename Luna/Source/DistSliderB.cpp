/*
  ==============================================================================

    DistSliderB.cpp
    Created: 8 Apr 2025 3:39:54pm
    Author:  Pedro Cajaty B. Braga

  ==============================================================================
*/

#include "DistSliderB.h"
#include "DistSliderBStyle.h"

DistSliderB::DistSliderB()
{
    slider.setSliderStyle(juce::Slider::LinearHorizontal);
    slider.setRange(0.0, 100.0, 0.1);
    slider.setValue(50.0);
//    DBG(slider.getValue());
    slider.setTextBoxStyle(juce::Slider::NoTextBox, true, 100, 25);
    
    slider.setLookAndFeel(&distLNF);
    slider.addListener(this);
    addAndMakeVisible(slider);
}

DistSliderB::~DistSliderB()
{
    // Clean up
    slider.setLookAndFeel(nullptr);
}

void DistSliderB::resized()
{
    slider.setBounds(getLocalBounds());
}

void DistSliderB::sliderValueChanged (juce::Slider* slider)
{
    // Checks if slider that was changed is this class state's slider
    if (slider == &this->slider)
    {
//        DBG("repainted");
//        DBG(slider->getValue());
        repaint();
    }
}

