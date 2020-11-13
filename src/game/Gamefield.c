#include "Gamefield.h"
#include <stdlib.h>
#include <glad/glad.h>

uint8_t * GetRawColor32Array(Gamefield *gamefield);

void InitGamefield(Gamefield* gamefield) {
    gamefield->width = WIDTH;
    gamefield->height = HEIGHT;
    gamefield->pixels = malloc(sizeof(Pixel) * gamefield->width * gamefield->height);

    glGenTextures(1, &gamefield->rendererId);
    glBindTexture(GL_TEXTURE_2D, gamefield->rendererId);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

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
    for (size_t i = 0; i < gamefield->height * gamefield->width; i++) {
        Pixel pixel;
        pixel.color.a = 1;
        pixel.color.r = (rand() / RAND_MAX) * 255;
        pixel.color.g = (rand() / RAND_MAX) * 255;
        pixel.color.b = (rand() / RAND_MAX) * 255;
        gamefield->pixels[i] = pixel;
    }

    uint8_t * rawPixelArray = GetRawColor32Array(gamefield);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, gamefield->width, gamefield->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, rawPixelArray);
    free(rawPixelArray);
}

uint8_t * GetRawColor32Array(Gamefield *gamefield) {
    uint8_t * pixelArray = malloc(gamefield->width * gamefield->height * 4);
    size_t pixelArrayIndex = 0;
    for (int i = 0; i < gamefield->width * gamefield->height; i++) {
        pixelArray[pixelArrayIndex++] = gamefield->pixels[i].color.r;
        pixelArray[pixelArrayIndex++] = gamefield->pixels[i].color.g;
        pixelArray[pixelArrayIndex++] = gamefield->pixels[i].color.b;
        pixelArray[pixelArrayIndex++] = gamefield->pixels[i].color.a;
    }
    return pixelArray;
}

