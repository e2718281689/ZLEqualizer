//
// Created by maple on 25-4-29.
//

#ifndef COEFFTABLE_H
#define COEFFTABLE_H

#include "../../gui/gui.hpp"
#include "../../../source/PluginProcessor.hpp"
#include "./TableModel.h"
namespace zlPanel {

    class CoeffTable final : public juce::Component,public juce::Timer
    {

    public:
        CoeffTable(PluginProcessor& p);
        ~CoeffTable() override;

        void paint(juce::Graphics &g) override;

        void resized() override;
        void timerCallback() override;
        void saveCoeff();
        void exportCoeff();

    private:
        PluginProcessor &processor;
        juce::Label dataLabel;

        juce::TextButton exportButton;

        juce::TableListBox table;



        juce::TableListBox coefftable;
        std::unique_ptr<juce::FileChooser> myChooser;

        inline auto static const settingDirectory =juce::File::getSpecialLocation(juce::File::userDesktopDirectory);

        std::vector<std::array<double,5>> coeffs;
        MyTableModel model;
    };
}

#endif //COEFFTABLE_H
