#include "noisemaker.h"
#include <limits>
using namespace std;

namespace noisemaker {
    int sampleRate = 44100;
    int maxFrequency = sampleRate / 2;
    sample maxSample = numeric_limits<writableSample>::max();
    sample minSample = numeric_limits<writableSample>::min();
}
