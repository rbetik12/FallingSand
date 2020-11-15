#include "Gamefield.h"
#include "../utils/ImageLoader.h"
#include <stdlib.h>
#include <stdio.h>
#include <glad/glad.h>
#include "../utils/Input.h"

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
    uint32_t x = 640;
    uint32_t y = 360;
    Pixel pixel;
    pixel.color.a = 255;
    pixel.color.r = 194;
    pixel.color.g = 178;
    pixel.color.b = 128;
    gamefield->pixels[y * gamefield->width + x] = pixel;

    uint8_t* rawPixelArray = NULL;
    if (rawPixelArray == NULL) {
        rawPixelArray = GetRawColor32Array(gamefield);
    }
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, gamefield->width, gamefield->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, rawPixelArray);
    free(rawPixelArray);
}

void OnGamefieldClick(Gamefield* gamefield, MousePos pos) {
    printf("Clicked at X: %f Y: %f\n", pos.x, pos.y);
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

