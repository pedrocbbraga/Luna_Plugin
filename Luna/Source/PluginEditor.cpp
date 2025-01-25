/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "MainComponent.h"

//==============================================================================
LunaAudioProcessorEditor::LunaAudioProcessorEditor (LunaAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p), mainComponent()
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    //auto sadMickey = juce::ImageCache::getFromMemory(BinaryData::sad_mickey_png, BinaryData::sad_mickey_pngSize);
    auto sadMickey = juce::ImageCache::getFromMemory(BinaryData::LunaPluginBG_png, BinaryData::LunaPluginBG_pngSize);
    
    if (! sadMickey.isNull())
        mImageComponent.setImage (sadMickey, juce::RectanglePlacement::stretchToFit);
    else
        jassert (! sadMickey.isNull());
    
    addAndMakeVisible(mImageComponent);
    
    setSize (800, 600);
    
    distSlider.setSliderStyle (juce::Slider::LinearBarVertical);
    distSlider.setRange (0.0, 100.0, 1.0);
    distSlider.setTextBoxStyle (juce::Slider::NoTextBox, false, 90, 0);
    distSlider.setPopupDisplayEnabled (true, false, this);
    distSlider.setTextValueSuffix (" Distortion");
    distSlider.setValue(1.0);
    distSlider.addListener(this);
    
    addAndMakeVisible (&distSlider);
    
    
    // THIS TURNS THE AUDIO WAVE JAWN ON/OFF
<<<<<<< Updated upstream
    // addAndMakeVisible(mainComponent);
=======
    addAndMakeVisible(mainComponent);
    mainComponent.setBounds(500, 400, 300, 225) ;
>>>>>>> Stashed changes
}

LunaAudioProcessorEditor::~LunaAudioProcessorEditor()
{
}

//==============================================================================
void LunaAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (juce::Colours::whitesmoke);

    g.setColour (juce::Colours::black);
    g.setFont (juce::FontOptions (22.0f));
    g.drawFittedText ("Luna Plugin on fucking god boul", getLocalBounds(), juce::Justification::bottomLeft, 1);
    g.drawFittedText ("Diode", 22, 5, getWidth(), 30, juce::Justification::topLeft, 1);
}

void LunaAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    
    // sets the position and size of the slider with arguments (x, y, width, height)
    distSlider.setBounds (40, 30, 20, getHeight() - 60);
    mImageComponent.setBoundsRelative(0.0f, 0.0f, 1.0f, 1.0f);
}

void LunaAudioProcessorEditor::sliderValueChanged (juce::Slider* slider)
{
    audioProcessor.distOnSlider = distSlider.getValue();
}
