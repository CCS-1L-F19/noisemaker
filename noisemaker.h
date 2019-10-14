// high level overview: Oscillators create sound
// all time values are in units of samples

#pragma once

#include <vector>
#include <limits>
#include <cassert>
#include <cinttypes>

typedef int16_t sample;

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

class LinearEnvelope: public Signal {
    public:
        struct Phase {
            sample value;
            int time;
            int timeInSamples();
        };
        sample step();
        LinearEnvelope();
        LinearEnvelope(std::vector<Phase> phasev);
        void setPhases(std::vector<Phase> phasev);
    private:
        int samplesElapsed;
        std::vector<Phase> phases;
};

class Oscillator: public Signal {
    public:
        sample step();

        static Oscillator sineWave(int frequency, Signal amplitudeSignal = Constant(std::numeric_limits<sample>::max()));

        Oscillator(int amp, std::vector<double> wtab);
        template<class S1, class S2> Oscillator(S1 ampSig, S2 incSig, std::vector<double> wtab) {
            setFieldsToZero();
            waveTable = wtab;
            setAmpSignal(ampSig);
            setIncrementSignal(incSig);
        }

        void setWaveTable(std::vector<double>);
        template <class T> void setAmpSignal(T s) {
            if (amplitudeSignal != NULL) { delete amplitudeSignal; }
            bool b = std::is_base_of<Signal, T>::value;
            assert(b);
            amplitudeSignal = new T(s);
        }

        template <class T> void setIncrementSignal(T s) {
            if (incrementSignal != NULL) { delete incrementSignal; }
            bool b = std::is_base_of<Signal, T>::value;
            assert(b);
            incrementSignal = new T(s);
        }
        Signal *amplitudeSignal;
        Signal *incrementSignal;
    private:
        std::vector<double> waveTable;
        int waveTableIndex;
        void setFieldsToZero();
 };

class Adder {};

class Multiplier {};