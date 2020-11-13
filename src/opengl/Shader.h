#pragma once

#include <stdint.h>

void InitShader(uint32_t * shaderId, const char* vertexSrc, const char* fragmentSrc);

void BindShader(const uint32_t * shaderId);

void UnBindShader(uint32_t * shaderId);

void SetUniform1i(uint32_t * shaderId, const char* name, int value);
