#include <glad/glad.h>
#include "Buffer.h"

void InitVertexArray(uint32_t * id) {
    glCreateVertexArrays(1, id);
}

void BindVertexArray(const uint32_t * id) {
    glBindVertexArray(*id);
}

void UnBindVertexArray(const uint32_t * id) {
    glBindVertexArray(0);
}

void AddVertexBuffer(const uint32_t * vertexArrayId, const uint32_t * vertexBufferId) {
    BindVertexArray(vertexArrayId);
    BindVertexBuffer(vertexBufferId);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0,
                          2, //2 floats per vertex coordinates
                          GL_FLOAT,
                          GL_FALSE, // we don't need to normalize coordinates of rect, because they're already within [-1; 1] range
                          sizeof(float) * 2, // total stride is 8 bytes (assuming that float is 4 bytes). 2 floats per vertex coords
                          0 // offset is 0, because vertex coordinates are first in a row
                          );

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1,
                          2, //2 floats per texture coordinates
                          GL_FLOAT,
                          GL_FALSE, // we don't need to normalize coordinates of rect, because they're already within [-1; 1] range
                          sizeof(float) * 2, // total stride is 8 bytes (assuming that float is 4 bytes). 2 floats per tex coords
                          (const void*) (sizeof(float) * 2) // offset is 8 bytes, because texture coordinates go after 2 floats of vertex coords
                          );
}

void AddIndexBuffer(const uint32_t * vertexArrayId, const uint32_t * indexBufferId) {
    BindVertexArray(vertexArrayId);
    BindIndexBuffer(indexBufferId);
}
