/*
  ==============================================================================

    DistSliderA.cpp
    Created: 26 Feb 2025 6:56:04pm
    Author:  Pedro Cajaty B. Braga

  ==============================================================================
*/

#include "DistSliderA.h"
#include "DistSliderAStyle.h"

DistSliderA::DistSliderA()
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

DistSliderA::~DistSliderA()
{
    // Clean up
    slider.setLookAndFeel(nullptr);
}

void DistSliderA::resized()
{
    slider.setBounds(getLocalBounds());
}

void DistSliderA::sliderValueChanged (juce::Slider* slider)
{
    // Checks if slider that was changed is this class state's slider
    if (slider == &this->slider)
    {
//        DBG("repainted");
//        DBG(slider->getValue());
        repaint();
    }
}
