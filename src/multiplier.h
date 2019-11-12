#pragma once

#include "noisemaker.h"
#include <vector>

class Multiplier : public Signal {
public:
    sample step();
    Multiplier(std::vector<Signal*> signals = {});
    std::vector<Signal*> managedSignals;
};
