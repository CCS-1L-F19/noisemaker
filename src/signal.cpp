#include "signal.h"
#include "noisemaker.h"
#include <cassert>

/**
 * Returns the value of this Signal after one step */
sample Signal::step() {
    // Signal should only be used as an abstract class and this function
    // should never be called
    assert(false);
    return 0;
}