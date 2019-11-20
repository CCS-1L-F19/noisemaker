#pragma once

#include "constant.h"

Constant::Constant(sample value) {
    this->value = value;
}

sample Constant::step() {
    return value;
}