// high level overview: Oscillators create sound

#include <cstdint>

typedef int16_t sample;

namespace noise {
    int sampleRate = 11025;
    class Signal;
    class Noisemaker;
    class Oscillator;
    class Adder;
    class Multiplier;
}

class noise::Signal {
    public:
        sample samples[10000];
        int currentSampleIndex;
        sample currentSample;
};

class noise::Noisemaker {
    public:
        virtual sample getSampleAtTime(int t) = 0;
};

class noise::Oscillator: noise::Noisemaker {
    public:
        sample getSampleAtTime(int t);

        void setInputAmplitude(Signal s);
        void setInputAmplitude(int i);
        void setSampleIncrement(Signal s);
        void setSampleIncrement(int i);
        void setWaveform(sample samples[], int size);
        void setWaveformUsingFunction(sample (*f)(int), int sampleNum);
};

class noise::Adder {};

class noise::Multiplier {};