#include <glad/glad.h>
#include "Buffer.h"

// Vertex Buffer definition ////////////////////////////////////////////////////////////////////////////////////

void InitVertexBuffer(uint32_t * vertexBufferId, float * vertices, uint32_t size) {
    glCreateBuffers(1, vertexBufferId);
    glBindBuffer(GL_ARRAY_BUFFER, *vertexBufferId);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

void BindVertexBuffer(const uint32_t * vertexBufferId) {
    glBindBuffer(GL_ARRAY_BUFFER, *vertexBufferId);
}

void UnBindVertexBuffer(uint32_t * vertexBufferId) {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

// Index Buffer definition ////////////////////////////////////////////////////////////////////////////////////

void InitIndexBuffer(uint32_t * indexBufferId, uint32_t* indices, uint32_t count) {
    glCreateBuffers(1, indexBufferId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *indexBufferId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
}

void BindIndexBuffer(const uint32_t * indexBufferId) {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *indexBufferId);
}

void UnBindIndexBuffer(uint32_t * indexBufferId) {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}