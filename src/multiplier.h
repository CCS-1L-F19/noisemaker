#pragma once

#include "noisemaker.h"
#include <vector>

/// This Signal is used to multiply other Signals together.
class Multiplier : public Signal {
public:
    sample step();
    Multiplier(std::vector<Signal*> signals = {});
    std::vector<Signal*> managedSignals;
};
