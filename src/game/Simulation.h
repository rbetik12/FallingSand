#pragma once

#include "Gamefield.h"

typedef struct UIntVec2 UIntVec2;

struct UIntVec2 {
    uint32_t x;
    uint32_t y;
};

void SandStep(Gamefield *gamefield, UIntVec2 coords);

void GetSand(struct Pixel *pixel);
void GetEmpty(struct Pixel *pixel);
void GetWater(struct Pixel *pixel);
