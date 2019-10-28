#pragma once

#include "noisemaker.h"
#include <vector>

class LinearEnvelope: public Signal {
    public:
        sample step();
        struct Phase {
            double value;
            double time;
            int timeInSamples();
            sample valueInSamples();
            bool operator>(Phase p);
            bool operator<(Phase p);
        };
        LinearEnvelope();
        LinearEnvelope(std::vector<Phase> phasev);
        void setPhases(std::vector<Phase> phasev);
    private:
        int samplesElapsed;
        std::vector<Phase> phases;
};