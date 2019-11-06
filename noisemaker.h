// high level overview: Oscillators create sound
// all time values are in units of samples

typedef short sample;

class Signal {
    public:
        virtual sample getSampleAtTime(int t);
};

class Envelope: Signal {
    public:
        Envelope();
        Envelope(int aDur, sample aSam, int dDur, sample dSam, int sDur, sample sSam, int rDur, sample rSam);

        setAttack(int duration, sample amplitude);
        setDecay(int duration, sample amplitude);
        setSustain(int duration, sample amplitude);
        setRelease(int duration, sample amplitude);

        getSampleAtTime(int t);
}

class Oscillator: Signal {
    public:
        sample getSampleAtTime(int t);

        Oscillator();
        Oscillator(Signal amplitude, int sampleIncrement = 1);
        Oscillator(int amplitude, int sampleIncrement = 1);

        void setInputAmplitude(Signal s);
        void setInputAmplitude(int i);
        void setSampleIncrement(int i);
        void setWaveform(sample samples[], int size);
        void setWaveformUsingFunction(sample (*f)(int), int sampleNum);

    private:
        sample *waveTable;
        int waveTableLength;
        int sampleIncrement;

};

class Adder {};

class Multiplier {};