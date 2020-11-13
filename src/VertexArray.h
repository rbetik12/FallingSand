#pragma once

#include <stdint.h>

void InitVertexArray(uint32_t * id);

void BindVertexArray(uint32_t * id);

void AddVertexBuffer(const uint32_t * vertexArrayId, const uint32_t * vertexBufferId);

void AddIndexBuffer(const uint32_t * vertexArrayId, const uint32_t * indexBufferId);