/*
  ==============================================================================

    MoonSlider.cpp
    Created: 5 Feb 2025 5:59:14pm
    Author:  Pedro Braga

  ==============================================================================
*/

#include "MoonSlider.h"

MoonSlider::MoonSlider()
{

    setRange(0.0, 1.0, 0.01);
    setSliderStyle(juce::Slider::LinearHorizontal);
    
    openGLContext.setRenderer(this);
    openGLContext.attachTo(*this);
    
    loadMoonTexture();
}

MoonSlider::~MoonSlider()
{
    // Detaches the OpenGL context (state/data)
    openGLContext.detach();
    
}

void MoonSlider::paint(juce::Graphics& g) {}

void MoonSlider::resized()
{
    // Called when the slider is resized (useful for OpenGL later)
}

void MoonSlider::loadMoonTexture()
{
    // Load the moon image from the JUCE resources
    moonImage = juce::ImageCache::getFromMemory(BinaryData::MoonImage_jpg, BinaryData::MoonImage_jpgSize);
    
    if (!moonImage.isValid())
    {
        DBG("ERROR: Moon image failed to load");
        jassertfalse;
    }
}

void MoonSlider::newOpenGLContextCreated()
{
    // Compile and link shaders
    shaderProgram.reset(new juce::OpenGLShaderProgram(openGLContext));

    const char* vertexShader = R"(
        attribute vec2 position;
        attribute vec2 texCoord;
        varying vec2 vTexCoord;
        void main()
        {
            vTexCoord = texCoord;
            gl_Position = vec4(position, 0.0, 1.0);
        }
    )";

    const char* fragmentShader = R"(
        varying vec2 vTexCoord;
        uniform sampler2D textureSampler;
        void main()
        {
            gl_FragColor = texture2D(textureSampler, vTexCoord);
        }
    )";

    if (shaderProgram->addVertexShader(vertexShader) &&
        shaderProgram->addFragmentShader(fragmentShader) &&
        shaderProgram->link())
    {
        positionAttrib.reset(new juce::OpenGLShaderProgram::Attribute(*shaderProgram, "position"));
        texCoordAttrib.reset(new juce::OpenGLShaderProgram::Attribute(*shaderProgram, "texCoord"));
        textureUniform.reset(new juce::OpenGLShaderProgram::Uniform(*shaderProgram, "textureSampler"));
    }
    else
    {
        jassertfalse;  // Shader compilation failed
    }
    
    // If image was loaded, load texture
    if (moonImage.isValid())
    {
        moonTexture.loadImage(moonImage); // JUCE OpenGLTexture.h handles texture creation
    }
}

void MoonSlider::renderOpenGL()
{
    // This method is called to render the OpenGL frame

    // Clear the OpenGL context with a black background
    juce::OpenGLHelpers::clear(juce::Colours::black);

//    if (moonTexture.getTextureID() != 0)
//    {
//        // Bind the texture
//        moonTexture.bind();
//        printf("Binding textures");
//    }
    
    if (moonTexture.getTextureID() != 0 && shaderProgram != nullptr)
        {
            shaderProgram->use();

            GLfloat quadVertices[] = {
                -0.5f,  0.5f,  0.0f, 0.0f,  // Top-left  (adjusted)
                 0.5f,  0.5f,  1.0f, 0.0f,  // Top-right (adjusted)
                -0.5f, -0.5f,  0.0f, 1.0f,  // Bottom-left (adjusted)
                 0.5f, -0.5f,  1.0f, 1.0f   // Bottom-right (adjusted)
            };

            openGLContext.extensions.glEnableVertexAttribArray(positionAttrib->attributeID);
            openGLContext.extensions.glEnableVertexAttribArray(texCoordAttrib->attributeID);

            openGLContext.extensions.glVertexAttribPointer(positionAttrib->attributeID, 2, juce::gl::GL_FLOAT, juce::gl::GL_FALSE, 4 * sizeof(GLfloat), quadVertices);
            openGLContext.extensions.glVertexAttribPointer(texCoordAttrib->attributeID, 2, juce::gl::GL_FLOAT, juce::gl::GL_FALSE, 4 * sizeof(GLfloat), quadVertices + 2);

            moonTexture.bind();
            textureUniform->set(0);

            juce::gl::glDrawArrays(juce::gl::GL_TRIANGLE_STRIP, 0, 4);

            openGLContext.extensions.glDisableVertexAttribArray(positionAttrib->attributeID);
            openGLContext.extensions.glDisableVertexAttribArray(texCoordAttrib->attributeID);
        }
}

void MoonSlider::openGLContextClosing()
{
    // This method is called before the OpenGL context is destroyed
    // If there is a texture loaded, delete that texture -- prevents memory leaks
    moonTexture.release(); // Release the texture --JUCE method
    shaderProgram.reset();
    positionAttrib.reset();
    texCoordAttrib.reset();
    textureUniform.reset();
}
