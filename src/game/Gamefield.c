#include "Gamefield.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <glad/glad.h>
#include "../utils/ImageLoader.h"
#include "Simulation.h"
#include "../utils/AudioManager.h"

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
        GetEmpty(&pixel);
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
            if (gamefield->pixels[y * gamefield->width + x].lastUpdatedFrameNumber == gamefield->simulationStep) continue;
            IntVec2 coords;
            coords.x = x;
            coords.y = y;
            if (gamefield->pixels[y * gamefield->width + x].pixelType == Sand) {
                SandStep(gamefield, coords);
            }
            else if (gamefield->pixels[y * gamefield->width + x].pixelType == Water) {
                WaterStep(gamefield, coords);
            }
            else if (gamefield->pixels[y * gamefield->width + x].pixelType == Smoke) {
                SmokeStep(gamefield, coords);
            }
            else if (gamefield->pixels[y * gamefield->width + x].pixelType == Fire) {
                FireStep(gamefield, coords);
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
        case Stone:
            GetStone(&pixel);
            break;
        case Empty:
            GetEmpty(&pixel);
            break;
        case Plant:
            GetPlant(&pixel);
            break;
        case Smoke:
            GetSmoke(&pixel);
            break;
        case Fire:
            GetFire(&pixel);
            break;
    }
    gamefield->pixels[(uint32_t) coords.y * gamefield->width + (uint32_t) coords.x] = pixel;
}

void OnGamefieldClick(Gamefield* gamefield, MousePos pos) {
    pos.y = gamefield->height - pos.y;
    IntVec2 coords;

    uint8_t radius = GetCurrentPixelsRadius();
    PixelType pixelType = GetCurrentPixelType();

    for (int width = pos.x - radius; width < pos.x + radius; width++) {
        for (int height = pos.y - radius; height < pos.y + radius; height++) {
            coords.x = width;
            coords.y = height;
            CreatePixel(gamefield, coords, pixelType);
        }
    }

    switch (pixelType) {
        case Sand:
            AudioManagerPlaySoundOnce(SandSpawn);
            break;
        case Plant:
            AudioManagerPlaySoundOnce(PlantSpawn);
            break;
        case Water:
            AudioManagerPlaySoundOnce(WaterSpawn);
            break;
        case Stone:
            AudioManagerPlaySoundOnce(StoneSpawn);
            break;
        case Fire:
            AudioManagerPlaySoundOnce(FireSpawn);
            break;
    }
}

void ClearGamefield(Gamefield *gamefield) {
    for (size_t y = 0; y < gamefield->height; y++) {
        for (size_t x = 0; x < gamefield->width; x++) {
            gamefield->pixels[y * gamefield->width + x].lastUpdatedFrameNumber = 0;
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

