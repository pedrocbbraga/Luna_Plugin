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
    : AudioProcessorEditor (&p), audioProcessor (p), mainComponent(p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    //auto sadMickey = juce::ImageCache::getFromMemory(BinaryData::sad_mickey_png, BinaryData::sad_mickey_pngSize);
    auto sadMickey = juce::ImageCache::getFromMemory(BinaryData::luna_ui_bg_800_600_1_png, BinaryData::luna_ui_bg_800_600_1_pngSize);
    
    if (! sadMickey.isNull())
        mImageComponent.setImage (sadMickey, juce::RectanglePlacement::stretchToFit);
    else
        jassert (! sadMickey.isNull());
    
    addAndMakeVisible(mImageComponent);
    
    setSize (800, 600);
    
    /* ----------- DIST SLIDER A ----------- */
    distSliderA.setSliderStyle (juce::Slider::RotaryHorizontalDrag);
    distSliderA.setRange (0.0, 10.0, 0.0);
    distSliderA.setColour(juce::Slider::ColourIds::trackColourId, juce::Colours::whitesmoke);
    distSliderA.setTextBoxStyle (juce::Slider::NoTextBox, false, 90, 0);
    distSliderA.setPopupDisplayEnabled (true, false, this);
    distSliderA.setTextValueSuffix (" Distortion");
    distSliderA.addListener(this);
    addAndMakeVisible (&distSliderA);
    
    /* ----------- DIST SLIDER B ----------- */
    distSliderB.setSliderStyle (juce::Slider::RotaryHorizontalDrag);
    distSliderB.setRange (0.0, 10.0, 0.0);
    distSliderB.setColour(juce::Slider::ColourIds::trackColourId, juce::Colours::whitesmoke);
    distSliderB.setTextBoxStyle (juce::Slider::NoTextBox, false, 90, 0);
    distSliderB.setPopupDisplayEnabled (true, false, this);
    distSliderB.setTextValueSuffix (" Distortion");
    distSliderB.addListener(this);
    addAndMakeVisible (&distSliderB);
    
    
    // THIS TURNS THE AUDIO WAVE JAWN ON/OFF
    addAndMakeVisible(mainComponent);
    mainComponent.setBounds(500, 400, 300, 225) ;

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
    distSliderA.setBounds(150, 200, 200, 200);
    distSliderB.setBounds(450, 200, 200, 200);
    mImageComponent.setBoundsRelative(0.0f, 0.0f, 1.0f, 1.0f);
}

void LunaAudioProcessorEditor::sliderValueChanged (juce::Slider* slider)
{
    audioProcessor.a = distSliderA.getValue();
    audioProcessor.b = distSliderB.getValue();
    
}
