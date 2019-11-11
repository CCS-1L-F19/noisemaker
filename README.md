Noisemaker is a digital audio synthesizer library. Right now, the user designs a sound and that sound can be written to a wav file.

# Installation

The only software required for this library is a C++ compiler and the C++ standard library.
Instructions for installing a compiler can be found [here](https://www.cs.odu.edu/~zeil/cs250PreTest/latest/Public/installingACompiler)
The project must be compiled with c++11 or higher.


# Usage

The basic workflow in noisemaker is as follows:
1. Create a custom instrument using Noisemaker classes
2. Read the samples of that instrument into an array
3. Write those samples into a wav file

Below is an exaple of how to create a 440hz sine wave:

    sample samples[100000];
    Constant c(noisemaker::maxSample*.5);
    Oscillator o = Oscillator::sineWave(440);
    
    for (int i = 0; i < numSamples; i++) {
     samples[i] = o.step();
    }
    writeWavFile(fopen("test.wav", "w"), samples, numSamples, noisemaker::sampleRate);

`sample` is the type that noisemaker uses to store samples. Right now it should be int16_t.

`Constant` is a subclass of the `Signal` class. All `Signal`s have a `step()` function that returns the next sample that the 
`Signal` has generated. For some `Signal`s this will vary from call to call, but for a `Constant`, `step()`'s return value
is unsurprisingly constant.

`Oscillator` is another `Signal`. Here we use the premade `Oscillator` returned by the `sineWave` function.
It returns samples that make a sine wave at the specified frequency.

In the following `for` loop, we write `Oscillator`'s `step()` values to an array

Finally we pass that array to the `writeWavFile` function. Its parameters are self-explanatory.
