#pragma once

#include "noisemaker.h"
#include "signal.h"
#include <vector>

/**
 * A type of Signal that returns values that vary linearly, determined by
 * its phases. For example, a LinearEnvelope created using the initializer
 * list `{{0, 0}, {.7, 2}}` will return `0` after its first `step()` call, 
 * `.35 * noisemaker::maxSample` after 1 second of being stepped, and 
 * `.7 * noisemaker::maxSample` after 2 seconds of being stepped. After
 * it runs out of phases it just continues to return whatever its last
 * phase's value was. */
class LinearEnvelope: public Signal {
    public:
    sample step();
        /**
         * A Phase consists of a time in seconds and a value between zero and one.
         * The time field determines when the LinearEnvelope will reach the
         * value field of the Phase. */
        struct Phase {
            double value;
            double time;
            /// Returns time * noisemaker::sampleRate
            int timeInTicks();
            /// Returns value * noisemaker::maxSamples
            sample valueInSamples();
            /// Compares two Phases using their `time` values
            bool operator>(Phase p);
            /// Compares two Phases using their `time` values
            bool operator<(Phase p);
        };
        LinearEnvelope();
        LinearEnvelope(std::vector<Phase> phasev);
        void setPhases(std::vector<Phase> phasev);
    private:
        int samplesElapsed;
        std::vector<Phase> phases;
};