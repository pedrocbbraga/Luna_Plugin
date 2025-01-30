#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent(LunaAudioProcessor& p)
    : processor(p), partsHeight(PARTS, 0.0f)
{
    // Make sure you set the size of the component after
    // you add any child components.
    setSize (300, 225);
    setFramesPerSecond (60); // This sets the frequency of the update calls.
    
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
    const auto& delayBuffer = processor.getDelayBuffer();

    if (delayBuffer.getNumChannels() > 0)
    {
        auto* readPointer = delayBuffer.getReadPointer(0); // Assuming mono visualization
        int bufferSize = delayBuffer.getNumSamples();

        // Map audio buffer data to `partsHeight`
        for (int i = 0; i < bufferSize; ++i)
        {
//                int bufferIndex = juce::jmap(i, 0, PARTS, 0, bufferSize - 1);
//                partsHeight[i] = readPointer[bufferIndex] * getHeight() / 2.0f;
            addNewSample(readPointer[i] * 1000.0f, 1024);
        }
    }
    repaint();
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    // Background Color
    g.fillAll (juce::Colour { 0xFF19191b });
    
    
    // Draws the sine wave segments
    g.setColour (juce::Colour {0xFF129183});
    
//    int partIndexOffset = -(PARTS / 2);
    
    const int numParts = static_cast<int>(partsHeight.size());
    const float partWidth = static_cast<float>(getWidth()) / numParts; // Width of each segment
    
    for (int i = 0; i < numParts; ++i)
    {
        const float x = i * partWidth;          // X position
        const float centerY = getHeight() / 2; // Vertical center
        const float partHeight = partsHeight[i]; // Current sample height
        
        if (partHeight > 0.0f)
        {
            g.fillRect(x, centerY - partHeight, partWidth, std::fabs(partHeight));
        }
        else if (partHeight < 0.0f)
        {
            g.fillRect(x, centerY, partWidth, std::fabs(partHeight));
        }
        else
        {
            g.fillRect(x, centerY, partWidth, 1.0f); // Small rectangle for zero values
        }
    }
}

void MainComponent::resized()
{
    // This is called when the MainContentComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
}

void MainComponent::addNewSample(float newSample, int sampleAmt)
{
    if (partsHeight.size() < sampleAmt)
    {
        partsHeight.push_back(newSample); // Fill up the vector initially
    }
    else
    {
        std::rotate(partsHeight.begin(), partsHeight.begin() + 1, partsHeight.end()); // Shift left
        partsHeight.back() = newSample; // Add the newest sample at the end
    }
}
