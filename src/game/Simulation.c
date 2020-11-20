#include <stdio.h>
#include "Simulation.h"

void GetSand(struct Pixel *pixel);
void GetEmpty(struct Pixel *pixel);
void SwapSandPixel(Gamefield * gamefield, UIntVec2 * old, UIntVec2 * new);

void SandStep(Gamefield* gamefield, UIntVec2 coords) {
    if (coords.y == 0) return;
    if (coords.y < 0) {
        struct UIntVec2 new;
        new.x = coords.x;
        new.y = 0;
        SwapSandPixel(gamefield, &coords, &new);
        return;
    }
    if (gamefield->pixels[(coords.y - 1) * gamefield->width + coords.x].pixelType != Empty &&
            gamefield->pixels[(coords.y - 1) * gamefield->width + (coords.x - 1)].pixelType != Empty &&
            gamefield->pixels[(coords.y - 1) * gamefield->width + (coords.x + 1)].pixelType != Empty) return;
    struct UIntVec2 new;
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

void SwapSandPixel(Gamefield * gamefield, UIntVec2 * old, UIntVec2 * new) {
    struct Pixel sandPixel;
    GetSand(&sandPixel);
    struct Pixel emptyPixel;
    GetEmpty(&emptyPixel);

    gamefield->pixels[old->y * gamefield->width + old->x] = emptyPixel;
    gamefield->pixels[new->y * gamefield->width + new->x] = sandPixel;
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

