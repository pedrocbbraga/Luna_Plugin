#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "MainComponent.h"
#include "MoonSlider.h"
#include "DistSliderA.h"
#include "DistSliderB.h"
#include "GraphicsVisualizer.h"

//==============================================================================
/**
*/
class LunaAudioProcessorEditor  : public juce::AudioProcessorEditor,
                                  private juce::Slider::Listener
{
public:
    LunaAudioProcessorEditor (LunaAudioProcessor&);
    ~LunaAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    void sliderValueChanged (juce::Slider* slider) override ;
    
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    LunaAudioProcessor& audioProcessor;
    
    juce::Slider distSliderA ;
    juce::Slider distSliderB ;
    juce::Slider dryWet ;
    
    MainComponent mainComponent;
    std::unique_ptr<GraphicsVisualizer> dryGraphics;
    std::unique_ptr<GraphicsVisualizer> wetGraphics;

    juce::ImageComponent mImageComponent;
    
    MoonSlider moonSlider;
    
    DistSliderA TESTdistSliderA;
    DistSliderB TESTdistSliderB;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LunaAudioProcessorEditor)
};
