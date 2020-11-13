#pragma once

#include <stdint.h>

// Vertex Buffer declaration ////////////////////////////////////////////////////////////////////////////////////

void InitVertexBuffer(uint32_t * vertexBufferId, float * vertices, uint32_t size);

void BindVertexBuffer(const uint32_t * vertexBufferId);

void UnBindVertexBuffer(uint32_t * vertexBufferId);

// Index Buffer declaration ////////////////////////////////////////////////////////////////////////////////////

void InitIndexBuffer(uint32_t * vertexBufferId, uint32_t* indices, uint32_t count);

void BindIndexBuffer(const uint32_t * vertexBufferId);

void UnBindIndexBuffer(uint32_t * vertexBufferId);