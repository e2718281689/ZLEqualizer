//
// Created by maple on 25-4-29.
//

#ifndef COEFFTABLE_H
#define COEFFTABLE_H

#include "../../gui/gui.hpp"

namespace zlPanel {

    class CoeffTable final : public juce::Component
    {

      public:
        CoeffTable();
        ~CoeffTable() override;

        void paint(juce::Graphics &g) override;

        void resized() override;



    };
}

#endif //COEFFTABLE_H
