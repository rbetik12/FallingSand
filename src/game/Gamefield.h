#pragma once

#include <stdint.h>
#include "Pixel.h"

struct Gamefield {
    uint32_t rendererId;
    uint32_t width, height;

    Pixel * pixels;
};
