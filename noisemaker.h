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
    extern int maxFrequency;
    extern sample maxSample;
    extern sample minSample;
}

class Signal {
    public:
        virtual sample step();
};

class Constant: public Signal {
    public:
        Constant(sample i);
        sample step();
    private:
        sample value;
};

class Oscillator: public Signal {
    public:
        sample step();

        // premade Oscillators
        template<class S>
            static Oscillator sineWave(double frequency, S amplitudeSignal);
        static Oscillator sineWave(double frequency = 440);

        // TODO: make deepcopy constructor.

        // constructors
        template<class S1, class S2>
            Oscillator(S1 ampSig, S2 freqSig, std::vector<double> wtab);

        // setters
        void setWaveTable(std::vector<double>);
        template <class T>
            void setAmpSignal(T s);
        template <class T>
            void setFrequencySignal(T s);
        
        double getIncrementValueForFrequency(double f);
        double getIncrementValueFromFrequencySignalValue(sample s);
        static Constant generateFrequencySignalWithValue(double v);
        static double interpretFrequencySignalValue(sample v);

        Signal *amplitudeSignal;
        Signal *frequencySignal;

        static const int defaultWaveTableSize = 1024;
    private:
        std::vector<double> waveTable;
        double waveTableIndex;
        void setFieldsToZero();
 };

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

class Adder : public Signal {
public:
    sample step();
    struct WeightedInputSignal {
    public:
        double weight;
        Signal *signal;
        template<typename S>
        WeightedInputSignal(S signal, double weight);
        template<typename S>
        void setSignal(S signal);
    };
    Adder(std::vector<WeightedInputSignal>);
private:
    std::vector<WeightedInputSignal> weightedSignals;
};

class Multiplier {};