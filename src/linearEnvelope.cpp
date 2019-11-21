#include "noisemaker.h"
#include "signal.h"
#include "linearEnvelope.h"
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <cassert>
#include <limits>
#include <algorithm>
#include <vector>
#include <type_traits>
using namespace std;

LinearEnvelope::LinearEnvelope(vector<Phase> phasev) {
    samplesElapsed = 0;
    setPhases(phasev);
}

void LinearEnvelope::setPhases(vector<Phase> phasev) {
    phases = phasev;
    sort(phases.begin(), phases.end());
}

int LinearEnvelope::Phase::timeInTicks() {
    return time * noisemaker::sampleRate;
}

bool LinearEnvelope::Phase::operator>(Phase p) {
    return time > p.time;
}

bool LinearEnvelope::Phase::operator<(Phase p) {
    return time < p.time;
}

sample LinearEnvelope::Phase::valueInSamples() {
    return value * noisemaker::maxSample;
}

sample LinearEnvelope::step() {
    for (int i = 0; i < phases.size() - 1; i++) {
        if (samplesElapsed >= phases.back().timeInTicks()) {
                samplesElapsed++;
                return phases.back().valueInSamples();
        }
        if (samplesElapsed <= phases[i+1].timeInTicks()) {
            int phaseDurationInSamples = (phases[i+1].timeInTicks() - phases[i].timeInTicks());
            assert(phaseDurationInSamples > 0);
            sample valueDelta = phases[i+1].valueInSamples() - phases[i].valueInSamples();
            double slope = (double) valueDelta / phaseDurationInSamples;
            int distanceIntoPhase = samplesElapsed - phases[i].timeInTicks(); 
            samplesElapsed++;
            return distanceIntoPhase * slope + phases[i].valueInSamples();
        }
    }
}