#include "noisemaker.h"
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <cassert>
#include <limits>
#include <algorithm>
#include <vector>
using namespace std;

namespace noisemaker {
    int sampleRate = 44100;
    int maxFrequency = sampleRate / 2;
    sample maxSample = numeric_limits<writableSample>::max();
    sample minSample = numeric_limits<writableSample>::min();
}

sample Signal::step() {
    // Signal should only be used as an abstract class and this function
    // should never be called
    assert(false);
    return 0;
}