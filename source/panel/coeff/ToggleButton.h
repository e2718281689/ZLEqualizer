//
// Created by maple on 25-4-30.
//

#ifndef TOGGLEBUTTON_H
#define TOGGLEBUTTON_H

#include "../../gui/gui.hpp"

class ToggleButton : public juce::Button
{
public:
    ToggleButton()
        : juce::Button("TriangleToggle")
    {
        setClickingTogglesState(true); // 点击切换 toggle 状态
    }

    void paintButton(juce::Graphics& g, bool isMouseOver, bool isButtonDown) override
    {
        auto bounds = getLocalBounds().toFloat().reduced(2.0f);
        float cornerRadius = 6.0f;

        // 背景颜色
        auto bgColor = isButtonDown ? juce::Colours::lightgrey.darker()
                       : isMouseOver ? juce::Colours::lightgrey
                                     : juce::Colours::whitesmoke;

        // 背景圆角矩形
        g.setColour(bgColor);
        g.fillRoundedRectangle(bounds, cornerRadius);

        // 描边
        g.setColour(juce::Colours::darkgrey);
        g.drawRoundedRectangle(bounds, cornerRadius, 1.5f);

        // 中心位置
        auto center = bounds.getCentre();
        float size = std::min(bounds.getWidth(), bounds.getHeight()) * 0.4f;

        // 构造朝右的三角形（▶）
        juce::Path triangle;
        triangle.startNewSubPath(center.x - size * 0.5f, center.y - size);
        triangle.lineTo(center.x + size * 0.5f, center.y);
        triangle.lineTo(center.x - size * 0.5f, center.y + size);
        triangle.closeSubPath();

        // 根据 toggle 状态旋转 90 度（展开 ▼）
        if (getToggleState())
        {
            triangle.applyTransform(juce::AffineTransform::rotation(
                juce::MathConstants<float>::pi / 2.0f,
                center.x, center.y));
        }

        // 三角形颜色
        g.setColour(juce::Colours::black);
        g.fillPath(triangle);
    }
};

#endif //TOGGLEBUTTON_H
