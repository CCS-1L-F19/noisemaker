#include "noisemaker.h"
#include <vector>
#include <limits>
#include <cassert>
#include <cinttypes>
using namespace std;

template<typename S>
void Adder::WeightedInputSignal::setSignal(S signal) {
    if (!this->signal) { delete this->signal; }
    this->signal = new S(signal);
}

template<typename S>
Adder::WeightedInputSignal::WeightedInputSignal(S signal, double weight) : weight(weight) {
    setSignal(signal);
}

Adder::Adder(vector<WeightedInputSignal> ws) {
    double sum = 0;
    for (WeightedInputSignal s: ws) {
        sum += s.weight;
    }
    assert(sum <= 1);
    weightedSignals = ws;
}

sample Adder::step() {
    double r = 0;
    for (WeightedInputSignal s : weightedSignals) {
        r += s.weight * s.signal->step(); 
    }
}