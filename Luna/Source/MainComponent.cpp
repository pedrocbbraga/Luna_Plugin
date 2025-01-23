/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
    : partsHeight (PARTS, 0.0f)
{
    // Make sure you set the size of the component after
    // you add any child components.
    setSize (800, 600);
    setFramesPerSecond (120); // This sets the frequency of the update calls.
    
    
    // Attach OpenGLContext to render using OpenGL *****************************
    openGLContext.attachTo (*this); // Use OpenGL to render just this Component
    
    /* The following alternative line uses OpenGL to render the top level parent
       Component and all sub Components. */
    // openGLContext.attachTo (*getTopLevelComponent());
}

MainComponent::~MainComponent()
{
}

//==============================================================================
void MainComponent::update()
{
    // This function is called at the frequency specified by the setFramesPerSecond() call
    // in the constructor. You can use it to update counters, animate values, etc.
    
    // This code moves an X position back and forth across the screen over time
    // to draw a sine wave relative to that position.
    if (isForward)
    {
        centeredXPosition += INCREMENT;
        if (centeredXPosition + INCREMENT > getWidth())
        {
            isForward = false;
            centeredXPosition -= INCREMENT;
            centeredXPosition -= INCREMENT;
        }
    }
    else
    {
        centeredXPosition -= INCREMENT;
        if (centeredXPosition < 0.0f)
        {
            isForward = true;
            centeredXPosition += INCREMENT;
            centeredXPosition += INCREMENT;
        }
    }
    
    int partIndexOffset = -(PARTS / 2);
    
    // I'm under the impression that if we change the source of this for loop to *channelData,
    // this will print our audio data.
    // We might also have to change the jawn that makes it go backwards after going forward
    for (auto & partHeight : partsHeight)
    {
        partHeight = sin (getPartDistanceOffset (partIndexOffset) / getWidth() * 10.0f) * 100.0f;
        partIndexOffset++;
    }
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    // Background Color
    g.fillAll (juce::Colour { 0xFF19191b });
    
    
    // Draws the sine wave segments
    g.setColour (juce::Colours::white);
    
    int partIndexOffset = -(PARTS / 2);
    for (auto & partHeight : partsHeight)
    {
        if (partHeight > 0.0f)
        {
            g.fillRect (getPartDistanceOffset (partIndexOffset), getHeight() / 2.0f - partHeight, INCREMENT, std::fabs (partHeight));
        }
        else if (partHeight < 0.0f)
        {
            g.fillRect (getPartDistanceOffset (partIndexOffset), getHeight() / 2.0f, INCREMENT, std::fabs (partHeight));
        }
        
        g.fillEllipse (getPartDistanceOffset (partIndexOffset) - 4.0f, getHeight() / 2.0f - partHeight, 10.0f, 10.0f);
    
        partIndexOffset++;
    }
}

void MainComponent::resized()
{
    // This is called when the MainContentComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
}
