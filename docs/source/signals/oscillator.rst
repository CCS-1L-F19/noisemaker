Oscillator
==========

Signal <- Oscillator

A type of Signal that produces a repeated pattern,
specified by its wavetable.

**Member Functions**

.. function:: Oscillator(Signal ampSig, Signal freqSig, std::vector<double> wtab)

    Creates an Oscillator with ``amplitudeSignal`` equal
    to ``ampSig`` and ``frequencySignal`` equal to ``freqSig``.
    It uses wtab at its wavetable.

.. function:: Oscillator()

    Zero initializes everything.

.. function:: void setWaveTable()
.. function:: void setAmpSignal()
.. function:: void setFrequencySignal()

.. function:: static sample generateSampleThatProducesFrequency(double f);

    Generates a sample that, when used as the amplitude of an
    Oscillator's ``frequencySignal``, will be interpreted as
    frequency ``f``.

**Member Fields**

.. function:: private Signal *frequencySignal

    This is the Signal that is used to determine the frequency
    of the Oscillator, but its frequency at a particular time
    isn't equal to this Signal's step() value. It's related.
    Use the helper member function ``generateSampleThatProducesFrequency(double f)``
    to find the value that should be used to produce a
    certain frequency.

.. function:: private Signal *amplitudeSignal

    This Signal determines the amplitude of the Oscillator.
