#pragma once

#include "Color32.h"
#include "PixelType.h"
#include "stdbool.h"

typedef struct Pixel Pixel;

struct Pixel {
    Color32 color;
    PixelType pixelType;
    bool isUpdated;
};
