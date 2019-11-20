#pragma once

#include "noisemaker.h"
#include <vector>

/**
 * Used for adding different signals together. Each signal can be assigned a weight. */
class Adder : public Signal {
public:
    sample step();
    /**
     *  Used for associating a signal with a weight.
     *  Can be constructed using an intitializer list `{signal, weight}` */
    struct WeightedInputSignal {
        double weight;
        Signal *signal;
        template<typename S>
        WeightedInputSignal(S signal, double weight);
        template<typename S>
        void setSignal(S signal);
    };

    /**
     * If safe is true then the Adder makes sure that the sum of
     * the weights in `signals` is less than or equal to one, to 
     * avoid clipping. */
    Adder(std::vector<WeightedInputSignal> signals, bool safe = true);
    std::vector<WeightedInputSignal> weightedSignals;
};

#include "adder.cpp"