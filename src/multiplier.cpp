#include "noisemaker.h"
#include "multiplier.h"
#include <vector>
#include <limits>
#include <cassert>
#include <cinttypes>
using namespace std;

Multiplier::Multiplier(std::vector<Signal*> signals) : signals(signals) {}

sample Multiplier::step() {
    if (signals.size() == 0)
        return 0;
    sample result = signals.front()->step();
    for (int i = 1; i < signals.size(); i++) {
        result *= signals[i]->step();
    }
    return result;
}