#include <stdio.h>
#include <stdbool.h>
#include "Simulation.h"

void SwapSandPixel(Gamefield * gamefield, IntVec2 * old, IntVec2 * new);
void SwapWaterPixel(Gamefield * gamefield, IntVec2 * old, IntVec2 * new);

void SandStep(Gamefield* gamefield, IntVec2 coords) {
    if (coords.y == 0) return;
    if (coords.y < 0) {
        struct IntVec2 new;
        new.x = coords.x;
        new.y = 0;
        SwapSandPixel(gamefield, &coords, &new);
        return;
    }
    if (gamefield->pixels[(coords.y - 1) * gamefield->width + coords.x].pixelType != Empty &&
            gamefield->pixels[(coords.y - 1) * gamefield->width + (coords.x - 1)].pixelType != Empty &&
            gamefield->pixels[(coords.y - 1) * gamefield->width + (coords.x + 1)].pixelType != Empty) return;
    struct IntVec2 new;
    if (gamefield->pixels[(coords.y - 1) * gamefield->width + coords.x].pixelType == Empty) {
        new.x = coords.x;
        new.y = coords.y;
        new.y -= 1;
        SwapSandPixel(gamefield, &coords, &new);
    }
    else if (gamefield->pixels[(coords.y - 1) * gamefield->width + (coords.x - 1)].pixelType == Empty) {
        new.x = coords.x;
        new.y = coords.y;
        new.y -= 1;
        new.x -= 1;
        SwapSandPixel(gamefield, &coords, &new);
    }
    else if (gamefield->pixels[(coords.y - 1) * gamefield->width + (coords.x + 1)].pixelType == Empty) {
        new.x = coords.x;
        new.y = coords.y;
        new.y -= 1;
        new.x += 1;
        SwapSandPixel(gamefield, &coords, &new);
    }
}

void WaterStep(Gamefield *gamefield, IntVec2 coords) {
    if (coords.y < 0) {
        struct IntVec2 new;
        new.x = coords.x;
        new.y = 0;
        SwapWaterPixel(gamefield, &coords, &new);
        return;
    }

    struct IntVec2 new;
    if ((coords.y - 1) >= 0 && gamefield->pixels[(coords.y - 1) * gamefield->width + coords.x].pixelType == Empty) {
        new.x = coords.x;
        new.y = coords.y;
        new.y -= 1;
        SwapWaterPixel(gamefield, &coords, &new);
    }
    else if ((coords.y - 1) >= 0 && gamefield->pixels[(coords.y - 1) * gamefield->width + (coords.x - 1)].pixelType == Empty) {
        new.x = coords.x;
        new.y = coords.y;
        new.y -= 1;
        new.x -= 1;
        SwapWaterPixel(gamefield, &coords, &new);
    }
    else if ((coords.y - 1) >= 0 && gamefield->pixels[(coords.y - 1) * gamefield->width + (coords.x + 1)].pixelType == Empty) {
        new.x = coords.x;
        new.y = coords.y;
        new.y -= 1;
        new.x += 1;
        SwapWaterPixel(gamefield, &coords, &new);
    }
    else if ((coords.x - 1) >= 0
             && gamefield->pixels[coords.y * gamefield->width + (coords.x - 1)].pixelType == Empty) {
        new.x = coords.x;
        new.y = coords.y;
        new.x -= 1;
        SwapWaterPixel(gamefield, &coords, &new);
    }
    else if ((coords.x + 1) < gamefield->width
    && gamefield->pixels[coords.y * gamefield->width + (coords.x + 1)].pixelType == Empty) {
        new.x = coords.x;
        new.y = coords.y;
        new.x += 1;
        SwapWaterPixel(gamefield, &coords, &new);
    }
}

void SwapSandPixel(Gamefield * gamefield, IntVec2 * old, IntVec2 * new) {
    struct Pixel sandPixel;
    GetSand(&sandPixel);
    struct Pixel emptyPixel;
    GetEmpty(&emptyPixel);

    sandPixel.isUpdated = true;
    emptyPixel.isUpdated = true;

    gamefield->pixels[old->y * gamefield->width + old->x] = emptyPixel;
    gamefield->pixels[new->y * gamefield->width + new->x] = sandPixel;
}

void SwapWaterPixel(Gamefield * gamefield, IntVec2 * old, IntVec2 * new) {
    struct Pixel waterPixel;
    GetWater(&waterPixel);
    struct Pixel emptyPixel;
    GetEmpty(&emptyPixel);

    waterPixel.isUpdated = true;
    emptyPixel.isUpdated = true;

    gamefield->pixels[old->y * gamefield->width + old->x] = emptyPixel;
    gamefield->pixels[new->y * gamefield->width + new->x] = waterPixel;
}

void GetSand(struct Pixel *pixel) {
    pixel->pixelType = Sand;
    pixel->color.a = 255;
    pixel->color.r = 194;
    pixel->color.g = 178;
    pixel->color.b = 128;
}

void GetEmpty(struct Pixel *pixel) {
    pixel->pixelType = Empty;
    pixel->color.a = 255;
    pixel->color.r = 0;
    pixel->color.g = 0;
    pixel->color.b = 0;
}

void GetWater(struct Pixel *pixel) {
    pixel->pixelType = Water;
    pixel->color.a = 255;
    pixel->color.r = 35;
    pixel->color.g = 137;
    pixel->color.b = 218;
}

