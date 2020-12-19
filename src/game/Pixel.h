#pragma once

#include "Color32.h"
#include "PixelType.h"
#include "stdbool.h"

typedef struct Pixel Pixel;

struct Pixel {
    Color32 color;
    PixelType pixelType;
    uint8_t lastUpdatedFrameNumber;
    uint32_t density;
    bool flameable;
};
