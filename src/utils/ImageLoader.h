#pragma once

#include <stdint.h>

uint8_t * LoadImage(const char * imagePath);
void FreeImage(uint8_t * imageBuffer);