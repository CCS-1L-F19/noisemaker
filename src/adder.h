#pragma once

#include "noisemaker.h"
#include <vector>

class Adder : public Signal {
public:
    sample step();
    /**
     *  Used for associating a signal with a weight.
     *  Can be constructed using an intitializer list {signal, weight} */
    struct WeightedInputSignal {
        double weight;
        Signal *signal;
        /// Constructs a WeightedinputSignal with signal `signal` and weight `weight`.
        template<typename S>
        WeightedInputSignal(S signal, double weight);
        template<typename S>
        void setSignal(S signal);
    };
    Adder(std::vector<WeightedInputSignal> signals, bool safe = true);
    std::vector<WeightedInputSignal> weightedSignals;
};

#include "adder.cpp"