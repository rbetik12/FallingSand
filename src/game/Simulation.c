#include <stdio.h>
#include "Simulation.h"

void SandStep(Gamefield* gamefield, struct Pixel pixel, UIntVec2* coords);
void GetSand(struct Pixel *pixel);
void GetEmpty(struct Pixel *pixel);

void Step(Gamefield* gamefield, struct Pixel pixel, UIntVec2* coords) {
    if (pixel.pixelType == Empty) return;
    if (pixel.pixelType == Sand)  {
        SandStep(gamefield, pixel, coords);
    }
}

void SandStep(Gamefield* gamefield, struct Pixel pixel, UIntVec2* coords) {
    if (coords->y <= 0 || coords->y - 1 <= 0) return;
    if (gamefield->pixels[(coords->y - 1) * gamefield->height + coords->x].pixelType != Empty) return;
    if (gamefield->pixels[(coords->y - 1) * gamefield->height + coords->x].pixelType == Empty) {
        Pixel emptyPixel;
        GetEmpty(&emptyPixel);
        gamefield->pixels[coords->y * gamefield->height + coords->x] = emptyPixel;
        coords->y -= 1;
        Pixel sandPixel;
        GetSand(&sandPixel);
        gamefield->pixels[(coords->y - 1) * gamefield->height + coords->x] = sandPixel;
    }
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

