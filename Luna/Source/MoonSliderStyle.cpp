/*
  ==============================================================================

    MoonSliderStyle.cpp
    Created: 21 Feb 2025 10:26:21am
    Author:  Pedro Cajaty B. Braga

  ==============================================================================
*/

#include "MoonSliderStyle.h"

MoonLNF::MoonLNF()
{
    moonImage = juce::ImageCache::getFromMemory(BinaryData::whiteMoon_png, BinaryData::whiteMoon_pngSize);
    blackCircle = juce::ImageCache::getFromMemory(BinaryData::blackCircle2_png, BinaryData::blackCircle2_pngSize);
}

MoonLNF::~MoonLNF()
{
    //Destructor
}

void MoonLNF::drawLinearSlider(juce::Graphics& g, int x, int y, int width, int height, float sliderPos, float minSliderPos, float maxSliderPos, const juce::Slider::SliderStyle style, juce::Slider& slider)
{
    /* --------------- BOILER PLATE SLIDER IMPLEMENTATION ------------------ */
    if (slider.isBar())
        {
            DBG("This jawn a bar fr");
            g.setColour(slider.findColour(juce::Slider::trackColourId));
            g.fillRect(slider.isHorizontal() ? juce::Rectangle<float>(static_cast<float>(x), static_cast<float>(y) + 0.5f, sliderPos - static_cast<float>(x), static_cast<float>(height) - 1.0f)
                                             : juce::Rectangle<float>(static_cast<float>(x) + 0.5f, sliderPos, static_cast<float>(width) - 1.0f, static_cast<float>(y) + (static_cast<float>(height) - sliderPos)));

            drawLinearSliderOutline(g, x, y, width, height, style, slider);
        }
        else
        {
            DBG("This jawn NOT a bar fr");
            auto isTwoVal = (style == juce::Slider::SliderStyle::TwoValueVertical || style == juce::Slider::SliderStyle::TwoValueHorizontal);
            auto isThreeVal = (style == juce::Slider::SliderStyle::ThreeValueVertical || style == juce::Slider::SliderStyle::ThreeValueHorizontal);

            auto trackWidth = juce::jmin(6.0f, slider.isHorizontal() ? static_cast<float>(height) * 0.25f : static_cast<float>(width) * 0.25f);

            juce::Point<float> startPoint(slider.isHorizontal() ? static_cast<float>(x) : static_cast<float>(x) + static_cast<float>(width) * 0.5f,
                                          slider.isHorizontal() ? static_cast<float>(y) + static_cast<float>(height) * 0.5f : static_cast<float>(height + y));

            juce::Point<float> endPoint(slider.isHorizontal() ? static_cast<float>(width + x) : startPoint.x,
                                        slider.isHorizontal() ? startPoint.y : static_cast<float>(y));

            
            
            
            
            /* --------------- SLIDER BACKGROUND FILL ------------------ */
            juce::Path backgroundTrack;
            backgroundTrack.startNewSubPath(startPoint);
            backgroundTrack.lineTo(endPoint);
            slider.setColour(juce::Slider::backgroundColourId, juce::Colours::goldenrod);
            g.setColour(slider.findColour(juce::Slider::backgroundColourId));
            
            // LOAD MOON IMAGE
            if (!moonImage.isNull())
            {
                g.drawImageWithin(moonImage, 0, 0, width * 1.1, height, juce::RectanglePlacement::stretchToFit);
            }

            // Original slider background path
            //g.strokePath(backgroundTrack, { trackWidth, juce::PathStrokeType::curved, juce::PathStrokeType::rounded });

            
            /* --------------- SLIDER FOREGROUND FILL ------------------ */
            juce::Path valueTrack;
            juce::Point<float> minPoint, maxPoint, thumbPoint;

            /* ---- MORE BOILER PLATE STUFF ---- */
            if (isTwoVal || isThreeVal)
            {
                minPoint = { slider.isHorizontal() ? minSliderPos : static_cast<float>(width) * 0.5f,
                             slider.isHorizontal() ? static_cast<float>(height) * 0.5f : minSliderPos };

                if (isThreeVal)
                    thumbPoint = { slider.isHorizontal() ? sliderPos : static_cast<float>(width) * 0.5f,
                                   slider.isHorizontal() ? static_cast<float>(height) * 0.5f : sliderPos };

                maxPoint = { slider.isHorizontal() ? maxSliderPos : static_cast<float>(width) * 0.5f,
                             slider.isHorizontal() ? static_cast<float>(height) * 0.5f : maxSliderPos };
            }
            else
            {
                auto kx = slider.isHorizontal() ? sliderPos : static_cast<float>(x) + static_cast<float>(width) * 0.5f;
                auto ky = slider.isHorizontal() ? static_cast<float>(y) + static_cast<float>(height) * 0.5f : sliderPos;

                minPoint = startPoint;
                maxPoint = { kx, ky };
            }
            auto thumbWidth = getSliderThumbRadius(slider);
            valueTrack.startNewSubPath(minPoint);
            valueTrack.lineTo(isThreeVal ? thumbPoint : maxPoint);
            g.setColour(slider.findColour(juce::Slider::trackColourId));
            
            // LOAD BLACK CIRCLE IMAGE
            float xOffset = maxPoint.x;
            DBG(height);
            DBG(xOffset);
            float range = log(240) - log (12);
            float hOffset = 1 + (log(xOffset) - log(12)) / range;
            float yOffset = -100 * (log(xOffset) - log(12)) / range;
            DBG("hOffset:" << hOffset);
            ellipsePath.addEllipse(23, 21, 195, 195);
            g.reduceClipRegion(ellipsePath); //POTENTIAL ERRORS HERE, CHECK LATER
            if (!blackCircle.isNull())
            {
                g.drawImageWithin(blackCircle, xOffset - 16, (y - 16) + yOffset, width + 30, (height + 30) * hOffset, juce::RectanglePlacement::stretchToFit);
            }
            
            // Original slider fill path
            //g.strokePath(valueTrack, { trackWidth, juce::PathStrokeType::curved, juce::PathStrokeType::rounded });

            if (!isTwoVal)
            {
                g.setColour(slider.findColour(juce::Slider::thumbColourId));
                // Original slider thumb
                //g.fillEllipse(juce::Rectangle<float>(static_cast<float>(thumbWidth), static_cast<float>(thumbWidth)).withCentre(isThreeVal ? thumbPoint : maxPoint));
            }

            /* ---- MORE BOILER PLATE STUFF ---- */
            if (isTwoVal || isThreeVal)
            {
                auto sr = juce::jmin(trackWidth, (slider.isHorizontal() ? static_cast<float>(height) : static_cast<float>(width)) * 0.4f);
                auto pointerColour = slider.findColour(juce::Slider::thumbColourId);

                if (slider.isHorizontal())
                {
                    drawPointer(g, minSliderPos - sr,
                                juce::jmax(0.0f, static_cast<float>(y) + static_cast<float>(height) * 0.5f - trackWidth * 2.0f),
                                trackWidth * 2.0f, pointerColour, 2);

                    drawPointer(g, maxSliderPos - trackWidth,
                                juce::jmin(static_cast<float>(y + height) - trackWidth * 2.0f, static_cast<float>(y) + static_cast<float>(height) * 0.5f),
                                trackWidth * 2.0f, pointerColour, 4);
                }
                else
                {
                    drawPointer(g, juce::jmax(0.0f, static_cast<float>(x) + static_cast<float>(width) * 0.5f - trackWidth * 2.0f),
                                minSliderPos - trackWidth,
                                trackWidth * 2.0f, pointerColour, 1);

                    drawPointer(g, juce::jmin(static_cast<float>(x + width) - trackWidth * 2.0f, static_cast<float>(x) + static_cast<float>(width) * 0.5f), maxSliderPos - sr,
                                trackWidth * 2.0f, pointerColour, 3);
                }
            }

            if (slider.isBar())
                drawLinearSliderOutline(g, x, y, width, height, style, slider);
        }
}
