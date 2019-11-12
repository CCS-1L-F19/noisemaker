Multiplier
==========

Multiplier <- Signal

This class multiplies different signals together.

**Member Fields**

.. function:: std::vector<Signal *> managedSignals

    A vector of signals that are managed by a Multiplier

**Member Functions**

.. function:: Multiplier(std::vector<Signal*> signals = {});

    Creates a Multiplier whose ``step()`` function returns the product of all of the Signals in the input vector.

.. function:: sample step()

    Returns the product of all of the step() functions in ``managedSignals``
