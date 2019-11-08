#pragma once

#include <vector>
#include "noisemaker.h"
#include "constant.h"

class Oscillator: public Signal {
    public:
        sample step();

        // premade Oscillators

        // TODO: make deepcopy constructor.

        // constructors
        template<class S1, class S2>
            Oscillator(S1 ampSig, S2 freqSig, std::vector<double> wtab);
        Oscillator();

        // setters
        void setWaveTable(std::vector<double>);
        template <class T>
            void setAmpSignal(T s);
        template <class T>
            void setFrequencySignal(T s);
        
        double getIncrementValueForFrequency(double f);
        double getIncrementValueFromFrequencySample(sample s);
        static sample generateSampleThatProducesFrequency(double v);
        static double interpretFrequencySample(sample v);

        Signal *amplitudeSignal;
        Signal *frequencySignal;

        static const int defaultWaveTableSize = 1000000;
    private:
        std::vector<double> waveTable;
        double waveTableIndex;
        void setFieldsToZero();
 };

#include "oscillator.cpp"