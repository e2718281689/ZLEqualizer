//
// Created by maple on 25-4-29.
//

#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include "../../gui/gui.hpp"

namespace zlPanel {
    class MyTableModel : public juce::TableListBoxModel
    {
    public:

        MyTableModel(std::vector<std::array<double,5>>& data):coeffdata(data)
        {

        }

        int getNumRows() override
        {
            return static_cast<int>(coeffdata.size());
        }

        void paintRowBackground(juce::Graphics& g, int rowNumber, int width, int height, bool rowIsSelected) override
        {
            g.fillAll(juce::Colours::lightblue);

        }

        void paintCell(juce::Graphics& g, int rowNumber, int columnId,
                       int width, int height, bool rowIsSelected) override
        {
            g.setColour(rowIsSelected ? juce::Colours::lightblue : juce::Colours::white);
            g.fillRect(0, 0, width, height);

            g.setColour(juce::Colours::black);
            g.drawRect(0, 0, width, height);

            juce::String text = getTextFor(rowNumber, columnId);
            g.drawText(text, 2, 0, width - 4, height, juce::Justification::centredLeft);
        }
    private:

        juce::String getTextFor(int row, int colId)
        {
            if (row >= 0 && row < (int)coeffdata.size())
            {
                int index = colId - 1; // 如果列 ID 是从 1 开始
                if (index >= 0 && index < 5)
                    return juce::String(coeffdata[row][index], 4); // 保留 4 位小数
            }

            return {};
        }

        std::vector<std::array<double,5>> &coeffdata;
    };
}
#endif //TABLEMODEL_H
