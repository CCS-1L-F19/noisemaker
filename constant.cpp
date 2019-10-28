#pragma once

#include "constant.h"

Constant::Constant(sample d) {
    value = d;
}

sample Constant::step() {
    return value;
}