#pragma once

#include "noisemaker.h"
#include <vector>

class Adder : public Signal {
public:
    sample step();
    struct WeightedInputSignal {
    public:
        double weight;
        Signal *signal;
        template<typename S>
        WeightedInputSignal(S signal, double weight);
        template<typename S>
        void setSignal(S signal);
    };
    Adder(std::vector<WeightedInputSignal>, bool safe = true);
private:
    std::vector<WeightedInputSignal> weightedSignals;
};

#include "adder.cpp"