#pragma once

#include "noisemaker.h"
#include "signal.h"

/// A type of Signal that always returns the same value
class Constant: public Signal {
    public:
        Constant(sample value);
        sample step();
    private:
        sample value;
};

#include "constant.cpp"