#include "noisemaker.h"
#include <cstring>
#include <cstdlib>
#include <cassert>
#include <vector>
#include <type_traits>
using namespace std;

namespace noisemaker {
    int sampleRate = 44100;
}

sample Signal::step() {
    return 0;
}

Constant::Constant(int i) {
    value = i;
}

sample Constant::step() {
    return value;
}

sample Oscillator::step() {
    int a = ampSignal->step();
    // int i = incrementSignal->step();
    int i = 1;
    if (waveTableIndex >= waveTable.size()) {
        waveTableIndex %= waveTable.size();
    }
    sample result = a * waveTable[waveTableIndex];
    waveTableIndex += i;
    return result;
}

void Oscillator::setWaveTableUsingFunction(sample (*f)(int), double waveDurationInSeconds) {
    for (int i = 0; i < waveDurationInSeconds * noisemaker::sampleRate; i++) {
        waveTable.clear();
        waveTable.push_back(f(i));
    } 
    // WORKING HERE
// 
//     
// 
// 
// 
// 
// 
// 
// 
// 
// 
// 
// 
}