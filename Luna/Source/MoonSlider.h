/*
  ==============================================================================

    MoonSlider.h
    Created: 5 Feb 2025 5:59:03pm
    Author:  Pedro Cajaty B. Braga

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include <juce_opengl/juce_opengl.h>
#include <juce_gui_basics/juce_gui_basics.h>

class MoonSlider : public juce::Slider, private juce::OpenGLRenderer
{
public:
    MoonSlider();
    ~MoonSlider() override;

    void paint(juce::Graphics& g) override;
    void resized() override;

private:
    void loadMoonTexture();
    
    void newOpenGLContextCreated() override;
    void renderOpenGL() override;
    void openGLContextClosing() override;
    
    juce::OpenGLContext openGLContext;
    juce::OpenGLTexture moonTexture;
    juce::Image moonImage;
    
    // OpenGL shader program
    std::unique_ptr<juce::OpenGLShaderProgram> shaderProgram;
    std::unique_ptr<juce::OpenGLShaderProgram::Attribute> positionAttrib, texCoordAttrib;
    std::unique_ptr<juce::OpenGLShaderProgram::Uniform> textureUniform;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MoonSlider)
};
