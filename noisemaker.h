// high level overview: Oscillators create sound
// all time values are in units of samples

#pragma once

#include <vector>
#include <cassert>

typedef signed short sample;

namespace noisemaker {
    extern int sampleRate;
}

class Signal {
    public:
        virtual sample step();
};

class Constant: public Signal {
    public:
        Constant(int i);
        sample step();
    private:
        int value;
};

class Envelope: public Signal {
    public:
        Envelope();
        Envelope(int aDur, sample aSam, int dDur, sample dSam, int sDur, sample sSam, int rDur, sample rSam);

        void setAttack(int duration, sample amplitude);
        void setDecay(int duration, sample amplitude);
        void setSustain(int duration, sample amplitude);
        void setRelease(int duration, sample amplitude);

        sample getSampleAtTime(int t);
};

class Oscillator: public Signal {
    public:
        sample step();

        static Oscillator sineWave(int frequency);

        // Oscillator(int amp, sample (*f)(int), int duration);
        Oscillator(int amp, std::vector<double> wtab);
        template<class T> Oscillator(T ampSig, std::vector<double> wtab) {
            waveTable = wtab;
            waveTableIndex = 0;
            ampSignal = NULL;
            setAmpSignal(ampSig);
        }

        void setWaveTableUsingFunction(sample (*f)(int), double waveDurationInSeconds);
        void setWaveTable(std::vector<double>);
        template <class T> void setAmpSignal(T s) {
            // if (ampSignal != NULL) { delete ampSignal; }
            bool b = std::is_base_of<Signal, T>::value;
            // std::assert(b);
            ampSignal = new T(s);
        }
        Signal *ampSignal;
        Signal *incrementSignal;
    private:
        std::vector<double> waveTable;
        int waveTableIndex;
};

class Adder {};

class Multiplier {};