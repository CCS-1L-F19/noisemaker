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

class Oscillator: public Signal {
    public:
        sample step();

        // premade Oscillators
        template<class S>
            static Oscillator sineWave(double frequency, S amplitudeSignal = Constant(std::numeric_limits<sample>::max()));

        // constructors
        template<class S1, class S2>
            Oscillator(S1 ampSig, S2 incSig, std::vector<double> wtab);

        // setters
        void setWaveTable(std::vector<double>);
        template <class T>
            void setAmpSignal(T s);
        template <class T>
            void setIncrementSignal(T s);

        Signal *amplitudeSignal;
        Signal *incrementSignal;
    private:
        std::vector<double> waveTable;
        int waveTableIndex;
        void setFieldsToZero();
 };

class LinearEnvelope: public Signal {
    public:
        struct Phase {
            double value;
            double time;
            int timeInSamples();
            sample valueInSamples();
            bool operator>(Phase p);
            bool operator<(Phase p);
        };
        sample step();
        LinearEnvelope();
        LinearEnvelope(std::vector<Phase> phasev);
        void setPhases(std::vector<Phase> phasev);
    private:
        int samplesElapsed;
        std::vector<Phase> phases;
};

class Adder {};

class Multiplier {};