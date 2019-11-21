#include "noisemaker.h"
#include "signal.h"
#include "multiplier.h"
#include <vector>
#include <limits>
#include <cassert>
#include <cinttypes>
using namespace std;

#include <iostream>

Multiplier::Multiplier(std::vector<Signal*> signals) : managedSignals(signals) {}

sample Multiplier::step() {
    if (managedSignals.size() == 0)
        return 0;
    sample result = managedSignals.front()->step();
    for (int i = 1; i < managedSignals.size(); i++) {
        result *= managedSignals[i]->step();
    }
    return result;
}