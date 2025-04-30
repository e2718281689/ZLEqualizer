//
// Created by maple on 25-4-29.
//

#include "CoeffTable.h"
#include "../../../source/PluginProcessor.hpp"

namespace zlPanel
{

    CoeffTable::CoeffTable(PluginProcessor& p)
        : processor(p),model(coeffs)
    {
        addAndMakeVisible(dataLabel);
        dataLabel.setText("This is some data", juce::dontSendNotification);  // 默认数据
        dataLabel.setColour(juce::Label::backgroundColourId, juce::Colours::lightgrey); // 背景色
        dataLabel.setColour(juce::Label::outlineColourId, juce::Colours::black);

        addAndMakeVisible(exportButton);
        exportButton.setButtonText("Export comff");

        exportButton.onClick = [this]() { saveCoeff(); };

        addAndMakeVisible(table);

        coeffs.clear();
        table.setModel(&model);

        table.getHeader().addColumn("A0 ", 1, 50);
        table.getHeader().addColumn("A1 ", 2, 50);
        table.getHeader().addColumn("A2 ", 3, 50);
        table.getHeader().addColumn("B1 ", 4, 50);
        table.getHeader().addColumn("B2 ", 5, 50);

        table.setHeaderHeight(25);
        table.setRowHeight(24);

        startTimer(1000);
    }

    CoeffTable::~CoeffTable()
    {
        stopTimer();
    }
    void CoeffTable::exportCoeff()
    {
        auto& Controller = processor.getController();
        auto& Filters = Controller.getFilters();

        auto& filterLRIndices = Controller.getfilterLRIndices();
        const auto &indices{filterLRIndices[0]};

        coeffs.clear();
        for (int i = 0; i < filterLRIndices[0].getmSize(); ++i)
        {

            auto& mFilter = Filters[indices[i]].getMainFilter();
            auto& filters = mFilter.getFilters();
            auto& mCoeff = filters[0].getmCoeff();

            coeffs.push_back(mCoeff);
        }

        table.updateContent();
        table.repaint();

    }
    void CoeffTable::saveCoeff()
    {
        myChooser = std::make_unique<juce::FileChooser>(
                   "Save the control settings...", settingDirectory.getChildFile("coeff.json"), "*.json",
                   true, false, nullptr);
        constexpr auto settingSaveFlags = juce::FileBrowserComponent::saveMode |
                                          juce::FileBrowserComponent::warnAboutOverwriting;
        myChooser->launchAsync(settingSaveFlags, [this](const juce::FileChooser &chooser)
        {
            if (chooser.getResults().size() <= 0) { return; }
            juce::File settingFile(chooser.getResult().withFileExtension("json"));
            if (settingFile.create())
            {
                juce::Array<juce::var> jsonArray;

                for (const auto& row : coeffs)
                {
                    juce::Array<juce::var> rowArray;
                    for (const auto& value : row)
                        rowArray.add(value);

                    jsonArray.add(rowArray);
                }

                juce::var jsonVar = jsonArray;
                juce::String jsonString = juce::JSON::toString(jsonVar);
                settingFile.replaceWithText(jsonString);
            }
        });
    }

    void CoeffTable::timerCallback()
    {
        exportCoeff();
    }

    void CoeffTable::paint(juce::Graphics &g)
    {
        g.fillAll(juce::Colours::blue); // 填充整个组件为蓝色
    }

    void CoeffTable::resized()
    {
        auto around = getLocalBounds().reduced(10);
        around.setHeight(around.getHeight()-60);
        table.setBounds(around);

        exportButton.setBounds(getLocalBounds().getWidth()-20-150, getLocalBounds().getHeight()-20-40, 150, 40);
    }

}