#include "Gamefield.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <glad/glad.h>
#include "../utils/ImageLoader.h"
#include "Simulation.h"

#define GAMEFIELD_SIZE WIDTH * HEIGHT

uint8_t* GetRawColor32Array(Gamefield* gamefield);

void InitGamefield(Gamefield* gamefield) {
    gamefield->width = WIDTH;
    gamefield->height = HEIGHT;
    gamefield->pixels = malloc(sizeof(Pixel) * gamefield->width * gamefield->height);
    gamefield->simulationStep = 0;

    glGenTextures(1, &gamefield->rendererId);
    glBindTexture(GL_TEXTURE_2D, gamefield->rendererId);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

    for (size_t i = 0; i < gamefield->height * gamefield->width; i++) {
        Pixel pixel;
        pixel.pixelType = Empty;
        pixel.color.a = 255;
        pixel.color.r = 0;
        pixel.color.g = 0;
        pixel.color.b = 0;
        gamefield->pixels[i] = pixel;
    }

    OnUpdateGamefield(gamefield);
    UnBindGamefield(gamefield);
}

void UnBindGamefield(Gamefield* gamefield) {
    glBindTexture(GL_TEXTURE_2D, 0);
}

void BindGamefield(uint32_t slot, Gamefield* gamefield) {
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, gamefield->rendererId);
}

void OnUpdateGamefield(Gamefield* gamefield) {
    gamefield->simulationStep += 1;
    for (size_t y = 0; y < gamefield->height; y++) {
        for (size_t x = 0; x < gamefield->width; x++) {
            gamefield->pixels[y * gamefield->width + x].isUpdated = false;
        }
    }
    for (size_t y = 0; y < gamefield->height; y++) {
        for (size_t x = 0; x < gamefield->width; x++) {
            if (gamefield->pixels[y * gamefield->width + x].isUpdated) continue;
            IntVec2 coords;
            coords.x = x;
            coords.y = y;
            if (gamefield->pixels[y * gamefield->width + x].pixelType == Sand) {
                SandStep(gamefield, coords);
            }
            else if (gamefield->pixels[y * gamefield->width + x].pixelType == Water) {
                WaterStep(gamefield, coords);
            }
        }
    }

    uint8_t* rawPixelArray = NULL;
    if (rawPixelArray == NULL) {
        rawPixelArray = GetRawColor32Array(gamefield);
    }
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, gamefield->width, gamefield->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, rawPixelArray);
    free(rawPixelArray);
}


void CreatePixel(Gamefield *gamefield, IntVec2 coords, PixelType type) {
    if (!WithinBounds(gamefield, coords.x, coords.y)) return;
    Pixel pixel;
    switch (type) {
        case Water:
            GetWater(&pixel);
            break;
        case Sand:
            GetSand(&pixel);
            break;
        case Empty:
            GetEmpty(&pixel);
            break;
    }
    gamefield->pixels[(uint32_t) coords.y * gamefield->width + (uint32_t) coords.x] = pixel;
}

void OnGamefieldClick(Gamefield* gamefield, MousePos pos) {
    pos.y = gamefield->height - pos.y;
    IntVec2 coords;
    coords.x = pos.x;
    coords.y = pos.y;

    CreatePixel(gamefield, coords, GetCurrentPixelType());

    coords.x = pos.x - 1;
    coords.y = pos.y - 1;
    CreatePixel(gamefield, coords, GetCurrentPixelType());

    coords.x = pos.x;
    coords.y = pos.y - 1;
    CreatePixel(gamefield, coords, GetCurrentPixelType());

    coords.x = pos.x + 1;
    coords.y = pos.y - 1;
    CreatePixel(gamefield, coords, GetCurrentPixelType());

    coords.x = pos.x - 1;
    coords.y = pos.y;
    CreatePixel(gamefield, coords, GetCurrentPixelType());

    coords.x = pos.x + 1;
    coords.y = pos.y;
    CreatePixel(gamefield, coords, GetCurrentPixelType());

    coords.x = pos.x - 1;
    coords.y = pos.y + 1;
    CreatePixel(gamefield, coords, GetCurrentPixelType());

    coords.x = pos.x;
    coords.y = pos.y + 1;
    CreatePixel(gamefield, coords, GetCurrentPixelType());

    coords.x = pos.x + 1;
    coords.y = pos.y + 1;
    CreatePixel(gamefield, coords, GetCurrentPixelType());
}

void ClearGamefield(Gamefield *gamefield) {
    for (size_t y = 0; y < gamefield->height; y++) {
        for (size_t x = 0; x < gamefield->width; x++) {
            gamefield->pixels[y * gamefield->width + x].isUpdated = false;
            gamefield->pixels[y * gamefield->width + x].pixelType = Empty;
            gamefield->pixels[y * gamefield->width + x].color.r = 0;
            gamefield->pixels[y * gamefield->width + x].color.g = 0;
            gamefield->pixels[y * gamefield->width + x].color.b = 0;
            gamefield->pixels[y * gamefield->width + x].color.a = 255;
        }
    }
}

uint8_t* GetRawColor32Array(Gamefield* gamefield) {
    uint8_t* pixelArray = malloc(gamefield->width * gamefield->height * 4);
    size_t pixelArrayIndex = 0;
    for (int i = 0; i < GAMEFIELD_SIZE; i++) {
        pixelArray[pixelArrayIndex++] = gamefield->pixels[i].color.r;
        pixelArray[pixelArrayIndex++] = gamefield->pixels[i].color.g;
        pixelArray[pixelArrayIndex++] = gamefield->pixels[i].color.b;
        pixelArray[pixelArrayIndex++] = gamefield->pixels[i].color.a;
    }
    return pixelArray;
}

