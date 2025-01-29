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
    // This function is called at the frequency specified by the setFramesPerSecond() call
    // in the constructor. You can use it to update counters, animate values, etc.
    
    // This code moves an X position back and forth across the screen over time
    // to draw a sine wave relative to that position.
    
    
    // Makes wave go forward?
//    if (isForward)
//    {
//        centeredXPosition += INCREMENT;
//        if (centeredXPosition + INCREMENT > getWidth() + 200)
//        {
//            isForward = false;
//            centeredXPosition -= INCREMENT;
//            centeredXPosition -= INCREMENT;
//        }
//    }
//    
//    // Makes wave go backward?
//    else
//    {
//        centeredXPosition -= INCREMENT;
//        if (centeredXPosition < 0.0f)
//        {
//            isForward = true;
//            centeredXPosition += INCREMENT;
//            centeredXPosition += INCREMENT;
//        }
//    }
//    
//    int partIndexOffset = -(PARTS / 2);
//    
//    // I'm under the impression that if we change the source of this for loop to *channelData,
//    // this will print our audio data.
//    // We might also have to change the jawn that makes it go backwards after going forward
//    for (auto & partHeight : partsHeight)
//    {
//        partHeight = sin (getPartDistanceOffset (partIndexOffset) / getWidth() * 20.0f) * 75.0f;
//        partIndexOffset++;
//    }
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
    
//    for (auto & partHeight : partsHeight)
//    {
//        
//        // RECTANGLES/LINES THAT FILL UP THE AUDIO WAVE
//        if (partHeight > 0.0f)
//        {
//            g.fillRect (getPartDistanceOffset (partIndexOffset), getHeight() / 2.0f - partHeight, INCREMENT, std::fabs (partHeight));
//        }
//        else if (partHeight < 0.0f)
//        {
//            g.fillRect (getPartDistanceOffset (partIndexOffset), getHeight() / 2.0f, INCREMENT, std::fabs (partHeight));
//        }
//        else if (partHeight == 0)
//        {
//            g.fillRect (getPartDistanceOffset (partIndexOffset), getHeight() / 2.0f, INCREMENT, std::fabs (partHeight));
//        }
//        
//        // LITTLE BALL AT THE TOP/BOTTOM OF EACH LINE OF THE AUDIO WAVE
//        //g.fillEllipse (getPartDistanceOffset (partIndexOffset) - 4.0f, getHeight() / 2.0f - partHeight, 10.0f, 10.0f);
//    
//        partIndexOffset++;
//    }
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
