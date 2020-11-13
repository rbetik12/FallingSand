#pragma once

#include <stdint.h>
#include "Pixel.h"
#include "../utils/Config.h"

typedef struct Gamefield Gamefield;

struct Gamefield {
    uint32_t rendererId;
    uint32_t width, height;

    Pixel * pixels;
};

void InitGamefield(Gamefield* gamefield);

void BindGamefield(uint32_t slot, Gamefield* gamefield);

void UnBindGamefield(Gamefield* gamefield);

void OnUpdateGamefield(Gamefield* gamefield);