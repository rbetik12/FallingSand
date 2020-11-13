#pragma once

struct GLContext {
    GLFWwindow * window;
    uint32_t vertexArrayId;
    uint32_t vertexBufferId;
    uint32_t indexBufferId;
    uint32_t basicShaderId;
};

void OnUpdate(struct GLContext const *info);