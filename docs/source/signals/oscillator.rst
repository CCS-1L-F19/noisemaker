Oscillator
==========

Signal <- Oscillator

A type of Signal that produces a repeated pattern,
specified by its wavetable.

**Member Functions**

.. function:: Oscillator(Signal ampSig, Signal freqSig, std::vector<double> wtab)

    Creates an Oscillator with amplitude equal to ampSig
    and frequency determined by, but not equal to freqSig.
    Use the helper member function ``generateSampleThatProducesFrequency(double f)``
    to find the value that should be used to produce a
    certain frequency.
