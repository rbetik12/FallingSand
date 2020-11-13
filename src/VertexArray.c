#include <glad/glad.h>

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
    glBindVertexArray(*vertexArrayId);


}
