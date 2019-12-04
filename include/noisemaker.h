#pragma once

#include <cinttypes>

typedef double sample;
typedef int16_t writableSample;

namespace noisemaker {
    /**
     * The amount of samples that should be played in one second
     * by some program interpreting noisemaker's output. Default
     * value is 44100.*/
    extern int sampleRate;
    /**
     * The maximum frequency that can be represented at the current
     * sampleRate without causing aliasing. Value is `sampleRate / 2`*/
    extern int maxFrequency;
    /// The maximum value of the `writableSample` datatype.
    extern sample maxSample;
    /// The minumum value of the `writableSample` datatype.
    extern sample minSample;
}

