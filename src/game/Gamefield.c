#include "Gamefield.h"
#include "../utils/ImageLoader.h"
#include <stdlib.h>
#include <stdio.h>
#include <glad/glad.h>
#include "../utils/Input.h"
#include "Simulation.h"

#define GAMEFIELD_SIZE WIDTH * HEIGHT

uint8_t* GetRawColor32Array(Gamefield* gamefield);

void InitGamefield(Gamefield* gamefield) {
    gamefield->width = WIDTH;
    gamefield->height = HEIGHT;
    gamefield->pixels = malloc(sizeof(Pixel) * gamefield->width * gamefield->height);

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
    for (size_t y = 0; y < gamefield->height; y++) {
        for (size_t x = 0; x < gamefield->width; x++) {
            UIntVec2 coords;
            coords.x = x;
            coords.y = y;
            Step(gamefield, gamefield->pixels[y * gamefield->height + x], &coords);
        }
    }


    uint8_t* rawPixelArray = NULL;
    if (rawPixelArray == NULL) {
        rawPixelArray = GetRawColor32Array(gamefield);
    }
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, gamefield->width, gamefield->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, rawPixelArray);
    free(rawPixelArray);
}

void OnGamefieldClick(Gamefield* gamefield, MousePos pos) {
    Pixel pixel;
    pixel.pixelType = Sand;
    pixel.color.a = 255;
    pixel.color.r = 194;
    pixel.color.g = 178;
    pixel.color.b = 128;
    pos.y = gamefield->height - pos.y;
    gamefield->pixels[(uint32_t) pos.y * gamefield->width + (uint32_t) pos.x] = pixel;
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

