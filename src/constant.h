#pragma once

#include "noisemaker.h"

class Constant: public Signal {
    public:
        Constant(sample i);
        sample step();
    private:
        sample value;
};

#include "constant.cpp"