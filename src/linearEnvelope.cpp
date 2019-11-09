#include "noisemaker.h"
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

int LinearEnvelope::Phase::timeInSamples() {
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
        if (samplesElapsed >= phases.back().timeInSamples()) {
                samplesElapsed++;
                return phases.back().valueInSamples();
        }
        if (samplesElapsed <= phases[i+1].timeInSamples()) {
            int phaseDurationInSamples = (phases[i+1].timeInSamples() - phases[i].timeInSamples());
            assert(phaseDurationInSamples > 0);
            sample valueDelta = phases[i+1].valueInSamples() - phases[i].valueInSamples();
            double slope = (double) valueDelta / phaseDurationInSamples;
            int distanceIntoPhase = samplesElapsed - phases[i].timeInSamples(); 
            samplesElapsed++;
            return distanceIntoPhase * slope + phases[i].valueInSamples();
        }
    }
}