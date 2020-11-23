#pragma once

#include <stdint.h>
#include "Pixel.h"
#include "../utils/Config.h"
#include "../utils/Input.h"

typedef struct Gamefield Gamefield;

struct Gamefield {
    uint32_t rendererId;
    uint32_t width, height;

    Pixel * pixels;
    uint8_t simulationStep;
};

void InitGamefield(Gamefield* gamefield);

void BindGamefield(uint32_t slot, Gamefield* gamefield);

void UnBindGamefield(Gamefield* gamefield);

void OnUpdateGamefield(Gamefield* gamefield);

void OnGamefieldClick(Gamefield* gamefield, MousePos pos);

void ClearGamefield(Gamefield *gamefield);