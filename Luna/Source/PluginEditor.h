#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "MainComponent.h"
#include "MoonSlider.h"

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

    juce::ImageComponent mImageComponent;
    
    MoonSlider moonSlider;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LunaAudioProcessorEditor)
};
