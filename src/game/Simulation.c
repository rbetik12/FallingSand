#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "Simulation.h"

void SwapSandPixel(Gamefield* gamefield, IntVec2* old, IntVec2* new);

void SwapWaterPixel(Gamefield* gamefield, IntVec2* old, IntVec2* new);

bool CheckDensity (Gamefield * gamefield, IntVec2* pixelCoords1, IntVec2* pixelCoords2);

void SwapSmokePixel(Gamefield * gamefield, IntVec2* old, IntVec2* new);

bool WithinBounds(Gamefield* gamefield, int x, int y) {
    return !(x < 0 || y < 0 || x >= gamefield->width || y >= gamefield->height);
}

void SandStep(Gamefield* gamefield, IntVec2 coords) {
    struct IntVec2 new;
    new.x = coords.x;
    new.y = coords.y + 1;
    if (WithinBounds(gamefield, coords.x, coords.y + 1) && CheckDensity(gamefield, &coords, &new)) {
        return;
    }

    if (WithinBounds(gamefield, coords.x, coords.y - 1) && gamefield->pixels[(coords.y - 1) * gamefield->width + coords.x].pixelType == Empty) {
        new.x = coords.x;
        new.y = coords.y;
        new.y -= 1;
        SwapSandPixel(gamefield, &coords, &new);
    }
        // check whether we can go either direction, that is done to simulate random behavior for particles
    else if (WithinBounds(gamefield, coords.x - 1, coords.y - 1) &&
             gamefield->pixels[(coords.y - 1) * gamefield->width + (coords.x - 1)].pixelType == Empty &&
             WithinBounds(gamefield, coords.x + 1, coords.y - 1) &&
             gamefield->pixels[(coords.y - 1) * gamefield->width + (coords.x + 1)].pixelType == Empty) {
        new.x = coords.x;
        new.y = coords.y;
        if (gamefield->simulationStep % 2 == 0) {
            new.y -= 1;
            new.x -= 1;
        } else {
            new.y -= 1;
            new.x += 1;
        }
        SwapSandPixel(gamefield, &coords, &new);
    } else if (WithinBounds(gamefield, coords.x - 1, coords.y - 1) &&
               gamefield->pixels[(coords.y - 1) * gamefield->width + (coords.x - 1)].pixelType == Empty) {
        new.x = coords.x;
        new.y = coords.y;
        new.y -= 1;
        new.x -= 1;
        SwapSandPixel(gamefield, &coords, &new);
    } else if (WithinBounds(gamefield, coords.x + 1, coords.y - 1) &&
               gamefield->pixels[(coords.y - 1) * gamefield->width + (coords.x + 1)].pixelType == Empty) {
        new.x = coords.x;
        new.y = coords.y;
        new.y -= 1;
        new.x += 1;
        SwapSandPixel(gamefield, &coords, &new);
    }
}

void WaterStep(Gamefield* gamefield, IntVec2 coords) {
    struct IntVec2 new;
    new.x = coords.x;
    new.y = coords.y + 1;

    if (WithinBounds(gamefield, coords.x, coords.y + 1) && CheckDensity(gamefield, &coords, &new)) {
        return;
    }

    if (WithinBounds(gamefield, coords.x, coords.y - 1) && gamefield->pixels[(coords.y - 1) * gamefield->width + coords.x].pixelType == Empty) {
        new.x = coords.x;
        new.y = coords.y;
        new.y -= 1;
        SwapWaterPixel(gamefield, &coords, &new);
    } else if (WithinBounds(gamefield, coords.x - 1, coords.y - 1) &&
               gamefield->pixels[(coords.y - 1) * gamefield->width + (coords.x - 1)].pixelType == Empty
               && WithinBounds(gamefield, coords.x + 1, coords.y - 1) &&
               gamefield->pixels[(coords.y - 1) * gamefield->width + (coords.x + 1)].pixelType == Empty) {
        new.x = coords.x;
        new.y = coords.y;
        if (gamefield->simulationStep % 2 == 0) {
            new.y -= 1;
            new.x -= 1;
        } else {
            new.y -= 1;
            new.x += 1;
        }
        SwapWaterPixel(gamefield, &coords, &new);
    } else if (WithinBounds(gamefield, coords.x - 1, coords.y - 1) &&
               gamefield->pixels[(coords.y - 1) * gamefield->width + (coords.x - 1)].pixelType == Empty) {
        new.x = coords.x;
        new.y = coords.y;
        new.y -= 1;
        new.x -= 1;
        SwapWaterPixel(gamefield, &coords, &new);
    } else if (WithinBounds(gamefield, coords.x + 1, coords.y - 1) &&
               gamefield->pixels[(coords.y - 1) * gamefield->width + (coords.x + 1)].pixelType == Empty) {
        new.x = coords.x;
        new.y = coords.y;
        new.y -= 1;
        new.x += 1;
        SwapWaterPixel(gamefield, &coords, &new);
    } else if (WithinBounds(gamefield, coords.x - 1, coords.y)
               && gamefield->pixels[coords.y * gamefield->width + (coords.x - 1)].pixelType == Empty
               && WithinBounds(gamefield, coords.x + 1, coords.y)
               && gamefield->pixels[coords.y * gamefield->width + (coords.x + 1)].pixelType == Empty) {
        new.x = coords.x;
        new.y = coords.y;
        if (gamefield->simulationStep % 2 == 0) {
            new.x -= 1;
        } else {
            new.x += 1;
        }
        SwapWaterPixel(gamefield, &coords, &new);
    } else if (WithinBounds(gamefield, coords.x - 1, coords.y)
               && gamefield->pixels[coords.y * gamefield->width + (coords.x - 1)].pixelType == Empty) {
        new.x = coords.x;
        new.y = coords.y;
        new.x -= 1;
        SwapWaterPixel(gamefield, &coords, &new);
    } else if (WithinBounds(gamefield, coords.x + 1, coords.y)
               && gamefield->pixels[coords.y * gamefield->width + (coords.x + 1)].pixelType == Empty) {
        new.x = coords.x;
        new.y = coords.y;
        new.x += 1;
        SwapWaterPixel(gamefield, &coords, &new);
    }
}

void SmokeStep(Gamefield* gamefield, IntVec2 coords) {
    struct IntVec2 new;
    new.x = coords.x;
    new.y = coords.y + 1;

    if (WithinBounds(gamefield, coords.x, coords.y + 1) && CheckDensity(gamefield, &coords, &new)) {
        return;
    }

    if (WithinBounds(gamefield, coords.x, coords.y + 1) && gamefield->pixels[(coords.y + 1) * gamefield->width + coords.x].pixelType == Empty) {
        new.x = coords.x;
        new.y = coords.y;
        new.y += 1;
        SwapSmokePixel(gamefield, &coords, &new);
    } else if (WithinBounds(gamefield, coords.x - 1, coords.y + 1) &&
               gamefield->pixels[(coords.y + 1) * gamefield->width + (coords.x - 1)].pixelType == Empty
               && WithinBounds(gamefield, coords.x + 1, coords.y + 1) &&
               gamefield->pixels[(coords.y + 1) * gamefield->width + (coords.x + 1)].pixelType == Empty) {
        new.x = coords.x;
        new.y = coords.y;
        if (gamefield->simulationStep % 2 == 0) {
            new.y += 1;
            new.x -= 1;
        } else {
            new.y += 1;
            new.x += 1;
        }
        SwapSmokePixel(gamefield, &coords, &new);
    } else if (WithinBounds(gamefield, coords.x - 1, coords.y + 1) &&
               gamefield->pixels[(coords.y + 1) * gamefield->width + (coords.x - 1)].pixelType == Empty) {
        new.x = coords.x;
        new.y = coords.y;
        new.y += 1;
        new.x -= 1;
        SwapSmokePixel(gamefield, &coords, &new);
    } else if (WithinBounds(gamefield, coords.x + 1, coords.y + 1) &&
               gamefield->pixels[(coords.y + 1) * gamefield->width + (coords.x + 1)].pixelType == Empty) {
        new.x = coords.x;
        new.y = coords.y;
        new.y += 1;
        new.x += 1;
        SwapSmokePixel(gamefield, &coords, &new);
    } else if (WithinBounds(gamefield, coords.x - 1, coords.y)
               && gamefield->pixels[coords.y * gamefield->width + (coords.x - 1)].pixelType == Empty
               && WithinBounds(gamefield, coords.x + 1, coords.y)
               && gamefield->pixels[coords.y * gamefield->width + (coords.x + 1)].pixelType == Empty) {
        new.x = coords.x;
        new.y = coords.y;
        if (gamefield->simulationStep % 2 == 0) {
            new.x -= 1;
        } else {
            new.x += 1;
        }
        SwapSmokePixel(gamefield, &coords, &new);
    } else if (WithinBounds(gamefield, coords.x - 1, coords.y)
               && gamefield->pixels[coords.y * gamefield->width + (coords.x - 1)].pixelType == Empty) {
        new.x = coords.x;
        new.y = coords.y;
        new.x -= 1;
        SwapSmokePixel(gamefield, &coords, &new);
    } else if (WithinBounds(gamefield, coords.x + 1, coords.y)
               && gamefield->pixels[coords.y * gamefield->width + (coords.x + 1)].pixelType == Empty) {
        new.x = coords.x;
        new.y = coords.y;
        new.x += 1;
        SwapSmokePixel(gamefield, &coords, &new);
    }
}

void SwapSandPixel(Gamefield* gamefield, IntVec2* old, IntVec2* new) {
    struct Pixel sandPixel;
    GetSand(&sandPixel);
    struct Pixel emptyPixel;
    GetEmpty(&emptyPixel);

    sandPixel.lastUpdatedFrameNumber = gamefield->simulationStep;
    emptyPixel.lastUpdatedFrameNumber = gamefield->simulationStep;

    gamefield->pixels[old->y * gamefield->width + old->x] = emptyPixel;
    gamefield->pixels[new->y * gamefield->width + new->x] = sandPixel;
}

void SwapWaterPixel(Gamefield* gamefield, IntVec2* old, IntVec2* new) {
    struct Pixel waterPixel;
    GetWater(&waterPixel);
    struct Pixel emptyPixel;
    GetEmpty(&emptyPixel);

    waterPixel.lastUpdatedFrameNumber = gamefield->simulationStep;
    emptyPixel.lastUpdatedFrameNumber = gamefield->simulationStep;

    gamefield->pixels[old->y * gamefield->width + old->x] = emptyPixel;
    gamefield->pixels[new->y * gamefield->width + new->x] = waterPixel;
}

void SwapPixels(Gamefield * gamefield, IntVec2* pixelCoords1, IntVec2* pixelCoords2) {
    struct Pixel pixel1 = gamefield->pixels[pixelCoords1->y * gamefield->width + pixelCoords1->x];
    struct Pixel pixel2 = gamefield->pixels[pixelCoords2->y * gamefield->width + pixelCoords2->x];

    gamefield->pixels[pixelCoords1->y * gamefield->width + pixelCoords1->x] = pixel2;
    gamefield->pixels[pixelCoords2->y * gamefield->width + pixelCoords2->x] = pixel1;
}

void SwapSmokePixel(Gamefield * gamefield, IntVec2* old, IntVec2* new) {
    struct Pixel smokePixel;
    struct Pixel emptyPixel;

    GetSmoke(&smokePixel);
    GetEmpty(&emptyPixel);

    Color32 oldColor = gamefield->pixels[old->y * gamefield->width + old->x].color;
    if (old->y < new->y) {
        smokePixel.color.r = oldColor.r - 1;
        smokePixel.color.g = oldColor.g - 1;
        smokePixel.color.b = oldColor.b - 1;
    }

    if ((smokePixel.color.r == 0
        && smokePixel.color.g == 0
        && smokePixel.color.b == 0)
        || new->y == gamefield->height) {
        GetEmpty(&smokePixel);
    }

    smokePixel.lastUpdatedFrameNumber = gamefield->simulationStep;
    emptyPixel.lastUpdatedFrameNumber = gamefield->simulationStep;

    gamefield->pixels[old->y * gamefield->width + old->x] = emptyPixel;
    gamefield->pixels[new->y * gamefield->width + new->x] = smokePixel;
}

bool CheckForDensitySwappability(PixelType pixelType) {
    switch (pixelType) {
        case Stone:
            return false;
        case Empty:
            return false;
        case Plant:
            return false;
        default:
            return true;
    }
}

bool CheckDensity (Gamefield * gamefield, IntVec2* pixelCoords1, IntVec2* pixelCoords2) {
    struct Pixel pixel1 = gamefield->pixels[pixelCoords1->y * gamefield->width + pixelCoords1->x];
    struct Pixel pixel2 = gamefield->pixels[pixelCoords2->y * gamefield->width + pixelCoords2->x];

    if (CheckForDensitySwappability(pixel2.pixelType) && pixel1.density < pixel2.density) {
        SwapPixels(gamefield, pixelCoords1, pixelCoords2);
        return true;
    }

    return false;
}

void GetSand(struct Pixel* pixel) {
    pixel->pixelType = Sand;
    pixel->color.a = 255;
    pixel->color.r = 194;
    pixel->color.g = 178;
    pixel->color.b = 128;
    pixel->density = 20;
}

void GetEmpty(struct Pixel* pixel) {
    pixel->pixelType = Empty;
    pixel->color.a = 255;
    pixel->color.r = 0;
    pixel->color.g = 0;
    pixel->color.b = 0;
    pixel->density = UINT32_MAX;
}

void GetStone(Pixel * pixel) {
    pixel->pixelType = Stone;
    pixel->color.a = 255;
    pixel->color.r = 115;
    pixel->color.g = 115;
    pixel->color.b = 115;
    pixel->density = UINT32_MAX;
}

void GetWater(struct Pixel* pixel) {
    pixel->pixelType = Water;
    pixel->color.a = 255;
    pixel->color.r = 35;
    pixel->color.g = 137;
    pixel->color.b = 218;
    pixel->density = 10;
}

static int plantColors[] = {55, 117, 50, 65, 145, 49, 35, 82, 25, 62, 150, 44, 81, 201, 56};
static int plantColorsIndexes[] = {0, 3, 6, 9, 12};

void GetPlant(struct Pixel* pixel) {
    uint8_t randomColorIndex = rand() % 5;
    pixel->pixelType = Plant;
    pixel->color.a = 255;
    pixel->color.r = plantColors[plantColorsIndexes[randomColorIndex]];
    pixel->color.g = plantColors[plantColorsIndexes[randomColorIndex] + 1];
    pixel->color.b = plantColors[plantColorsIndexes[randomColorIndex] + 2];
    pixel->density = UINT32_MAX;
}


static int smokeColors[] = {117, 117, 117, 100, 100, 100, 105, 105, 105, 90, 90, 90, 95, 95, 95};
static int smokeColorsIndexes[] = {0, 3, 6, 9, 12};

void GetSmoke(struct Pixel* pixel) {
    uint8_t randomColorIndex = rand() % 5;
    pixel->pixelType = Smoke;
    pixel->color.a = 255;
    pixel->color.r = smokeColors[smokeColorsIndexes[randomColorIndex]];
    pixel->color.g = smokeColors[smokeColorsIndexes[randomColorIndex] + 1];
    pixel->color.b = smokeColors[smokeColorsIndexes[randomColorIndex] + 2];
    pixel->density = 0;
}

