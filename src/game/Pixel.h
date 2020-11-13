#pragma once

#include "Color32.h"
#include "PixelType.h"

typedef struct Pixel Pixel;

struct Pixel {
    Color32 color;
    PixelType pixelType;
};
