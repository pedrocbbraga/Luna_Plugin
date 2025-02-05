#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "MainComponent.h"
#include "MoonSlider.h"

//==============================================================================
LunaAudioProcessorEditor::LunaAudioProcessorEditor (LunaAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p), mainComponent(p)
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
    
    /* ----------- DIST SLIDER A ----------- */
    distSliderA.setSliderStyle (juce::Slider::RotaryVerticalDrag);
    distSliderA.setRange (0.0, 10.0, 0.1);
    distSliderA.setColour(juce::Slider::ColourIds::trackColourId, juce::Colours::whitesmoke);
    distSliderA.setTextBoxStyle (juce::Slider::NoTextBox, false, 90, 0);
    distSliderA.setPopupDisplayEnabled (true, false, this);
    distSliderA.setTextValueSuffix (" Dist A");
    distSliderA.addListener(this);
    addAndMakeVisible (&distSliderA);
    
    /* ----------- DIST SLIDER B ----------- */
    distSliderB.setSliderStyle (juce::Slider::RotaryVerticalDrag);
    distSliderB.setRange (0.0, 10.0, 0.1);
    distSliderB.setColour(juce::Slider::ColourIds::trackColourId, juce::Colours::whitesmoke);
    distSliderB.setTextBoxStyle (juce::Slider::NoTextBox, false, 90, 0);
    distSliderB.setPopupDisplayEnabled (true, false, this);
    distSliderB.setTextValueSuffix (" Dist B");
    distSliderB.addListener(this);
    addAndMakeVisible (&distSliderB);
    
    // Audio wave input visualizer make visible + setter
    addAndMakeVisible(mainComponent);
    mainComponent.setBounds(500, 400, 300, 225) ;
    
    addAndMakeVisible(moonSlider);
    moonSlider.setBounds(250, 175, 300, 225) ;
    
    
    

}

LunaAudioProcessorEditor::~LunaAudioProcessorEditor()
{
}

//==============================================================================
void LunaAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll (juce::Colours::whitesmoke);

    g.setColour (juce::Colours::black);
    g.setFont (juce::FontOptions (22.0f));
    g.drawFittedText ("Luna Plugin on fucking god boul", getLocalBounds(), juce::Justification::bottomLeft, 1);
    g.drawFittedText ("Diode", 22, 5, getWidth(), 30, juce::Justification::topLeft, 1);
}

void LunaAudioProcessorEditor::resized()
{
    // sets the position and size of the slider with arguments (x, y, width, height)
//    distSliderA.setBounds(150, 200, 200, 200);
//    distSliderB.setBounds(450, 200, 200, 200);
    distSliderA.setBounds(30, 500, 90, 90);
    distSliderB.setBounds(130, 500, 90, 90);
    mImageComponent.setBoundsRelative(0.0f, 0.0f, 1.0f, 1.0f);
}

void LunaAudioProcessorEditor::sliderValueChanged (juce::Slider* slider)
{
    audioProcessor.a = distSliderA.getValue();
    audioProcessor.b = distSliderB.getValue();
    
}
