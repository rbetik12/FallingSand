#pragma once

#include "Gamefield.h"

typedef struct IntVec2 IntVec2;

struct IntVec2 {
    int x;
    int y;
};

void SandStep(Gamefield *gamefield, IntVec2 coords);
void WaterStep(Gamefield *gamefield, IntVec2 coords);

void GetSand(struct Pixel *pixel);
void GetEmpty(struct Pixel *pixel);
void GetWater(struct Pixel *pixel);
