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
    auto sadMickey = juce::ImageCache::getFromMemory(BinaryData::LunaPluginBG5_png, BinaryData::LunaPluginBG5_pngSize);
    
    if (! sadMickey.isNull())
        mImageComponent.setImage (sadMickey, juce::RectanglePlacement::stretchToFit);
    else
        jassert (! sadMickey.isNull());
    
    addAndMakeVisible(mImageComponent);
    setSize (800, 600);
    
    
    /* ----------------- GRAPHICS VISUALIZERS ----------------- */
    // INPUT
    dryGraphics = std::make_unique<GraphicsVisualizer>(
                        audioProcessor,
                        [this]() -> const juce::AudioBuffer<float>& { return audioProcessor.getDelayBuffer(); },
                        juce::Colour (0xff6C158C));
    dryGraphics->setBounds(0, getHeight() / 2 - 100, getWidth() / 3 + 30, getHeight() / 3) ;
    addAndMakeVisible(*dryGraphics);
    
    // OUTPUT
    wetGraphics = std::make_unique<GraphicsVisualizer>(
                        audioProcessor,
                        [this]() -> const juce::AudioBuffer<float>& { return audioProcessor.getDelayBufferPost(); },
                        juce::Colour (0xff6C158C));
    wetGraphics->setBounds(490, getHeight() / 2 - 100, getWidth() / 3 + 50, getHeight() / 3) ;
    addAndMakeVisible(*wetGraphics);
    
//    DBG("Width: " << getWidth());
//    DBG("Height: " << getHeight());
    
    // Moon slider jawn
    addAndMakeVisible(moonSlider);
    moonSlider.setBounds(275, 180, 250, 250);
    
    // TEST DIST SLIDER A
    addAndMakeVisible(TESTdistSliderA);
    TESTdistSliderA.setBounds(275, 400, 150, 250);
    
    // TEST DIST SLIDER B
    addAndMakeVisible(TESTdistSliderB);
    TESTdistSliderB.setBounds(375, 400, 150, 250);
    
    moonAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
        audioProcessor.treeState, "moonDryWet", moonSlider.slider);

    distAAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
        audioProcessor.treeState, "distA", TESTdistSliderA.slider);

    distBAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
        audioProcessor.treeState, "distB", TESTdistSliderB.slider);

}

LunaAudioProcessorEditor::~LunaAudioProcessorEditor()
{
    moonAttachment = nullptr;
    distAAttachment = nullptr;
    distBAttachment = nullptr;
}

//==============================================================================
void LunaAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll (juce::Colours::black);

    g.setColour (juce::Colours::black);
    g.setFont (juce::FontOptions (22.0f));
    g.drawFittedText ("Luna Plugin on fucking god boul", getLocalBounds(), juce::Justification::bottomLeft, 1);
    g.drawFittedText ("Diode", 22, 5, getWidth(), 30, juce::Justification::topLeft, 1);
}

void LunaAudioProcessorEditor::resized()
{
    // sets the position and size of the slider with arguments (x, y, width, height)
    distSliderA.setBounds(30, 500, 90, 90);
    distSliderB.setBounds(130, 500, 90, 90);
    dryWet.setBounds(300, 200, 200, 200);
    mImageComponent.setBoundsRelative(0.0f, 0.0f, 1.0f, 1.0f);
}

//void LunaAudioProcessorEditor::sliderValueChanged (juce::Slider* slider)
//{
////    audioProcessor.a = TESTdistSliderA.slider.getValue()/10;
//////    DBG(TESTdistSliderA.slider.getValue());
////    audioProcessor.b = TESTdistSliderB.slider.getValue()/10;
////    audioProcessor.dw = moonSlider.slider.getValue()/100;
//////    DBG(moonSlider.slider.getValue());
//}
