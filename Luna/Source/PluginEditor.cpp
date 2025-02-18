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
    distSliderA.setSliderStyle (juce::Slider::RotaryHorizontalDrag);
    distSliderA.setRange (0.0, 100.0, 1.0);
    distSliderA.setColour(juce::Slider::ColourIds::trackColourId, juce::Colours::whitesmoke);
    distSliderA.setTextBoxStyle (juce::Slider::NoTextBox, false, 90, 0);
    distSliderA.setPopupDisplayEnabled (true, false, this);
    distSliderA.setTextValueSuffix (" Distortion");
    distSliderA.addListener(this);
    addAndMakeVisible (&distSliderA);
    
    /* ----------- DIST SLIDER B ----------- */
    distSliderB.setSliderStyle (juce::Slider::RotaryHorizontalDrag);
    distSliderB.setRange (0.0, 100.0, 1.0);
    distSliderB.setColour(juce::Slider::ColourIds::trackColourId, juce::Colours::whitesmoke);
    distSliderB.setTextBoxStyle (juce::Slider::NoTextBox, false, 90, 0);
    distSliderB.setPopupDisplayEnabled (true, false, this);
    distSliderB.setTextValueSuffix (" Distortion");
    distSliderB.addListener(this);
    addAndMakeVisible (&distSliderB);
    
    /*------------ DRY WET SLIDER -----------*/
//    dryWet.setSliderStyle(juce::Slider::LinearHorizontal);
//    dryWet.setRange(0.0, 100.0, 1.0);
//    dryWet.setColour(juce::Slider::ColourIds::trackColourId, juce::Colours::whitesmoke);
//    dryWet.setTextBoxStyle (juce::Slider::NoTextBox, false, 90, 0);
//    dryWet.setPopupDisplayEnabled (true, false, this);
//    dryWet.setTextValueSuffix(" Dry/Wet");
//    dryWet.addListener(this);
//    addAndMakeVisible (&dryWet);
    

    // THIS TURNS THE AUDIO WAVE JAWN ON/OFF
    addAndMakeVisible(mainComponent);
    mainComponent.setBounds(500, 400, 300, 225) ;
    
//    moonSlider.setSize(400, 400);
    addAndMakeVisible(moonSlider);
    moonSlider.setBounds(200, 200, 400, 400);

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
    distSliderA.setBounds(100, 200, 200, 200);
    distSliderB.setBounds(500, 200, 200, 200);
    dryWet.setBounds(300, 200, 200, 200);
    mImageComponent.setBoundsRelative(0.0f, 0.0f, 1.0f, 1.0f);
}

void LunaAudioProcessorEditor::sliderValueChanged (juce::Slider* slider)
{
    audioProcessor.a = distSliderA.getValue();
    audioProcessor.b = distSliderB.getValue();
    audioProcessor.dw = dryWet.getValue()/100;
    
}
