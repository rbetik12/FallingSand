#pragma once

#include "Gamefield.h"

typedef struct UIntVec2 UIntVec2;

struct UIntVec2 {
    uint32_t x;
    uint32_t y;
};

void Step(Gamefield* gamefield, struct Pixel pixel, UIntVec2* coords);
