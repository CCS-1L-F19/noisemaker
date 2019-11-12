Adder
=====

Adder <- Signal

This class adds different signals together.

**Member Fields**

.. function:: std::vector<WeightedInputSignal> weighedSignals

    A vector of all of the signals that an Adder will sum

**Member Functions**

.. function:: Adder(std::vector<WeightedInputSignal> signals = {}, bool safe = true)

    Creates an Adder whose ``step()`` function returns the sum
    of all of the Signals in the input vector. When ``safe`` is true,
    the adder will check that the sums of the weights of all of the
    ``WeightedInputSignal``s is less than or equal to one, in order
    to avoid clipping.

    | **Note:** WeightedInputSignals can be constructed using an initializer list.

    .. code-block:: c++

        Adder a = Adder({{firstSignal, .6}, {secondSignal, .4}}, true)

**Member Types**

.. function:: WeightedInputSignal(S signal, double weight)

    A class used by Adder to keep track of signals and weights.
