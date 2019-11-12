#pragma once

#include "noisemaker.h"
#include <vector>

class Adder : public Signal {
public:
    sample step();
    struct WeightedInputSignal {
        double weight;
        Signal *signal;
        template<typename S>
        WeightedInputSignal(S signal, double weight);
        template<typename S>
        void setSignal(S signal);
    };
    Adder(std::vector<WeightedInputSignal> signals, bool safe = true);
    std::vector<WeightedInputSignal> weightedSignals;
};

#include "adder.cpp"