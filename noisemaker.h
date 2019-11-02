// high level overview: Oscillators create sound

#include <cstdint>

typedef int16_t sample;

class Signal {
    public:
        sample samples[10000];
        int currentSampleIndex;
        sample currentSample;
};

class Noisemaker {
    public:
        virtual sample getSampleAtTime(int t) = 0;
};

class Oscillator: Noisemaker {
    public:
        sample getSampleAtTime(int t);

        void setInputAmplitude(Signal s);
        void setInputAmplitude(int i);
        void setSampleIncrement(Signal s);
        void setSampleIncrement(int i);
        void setWaveform(int a[], int size);
};

class Adder {};

class Multiplier {};