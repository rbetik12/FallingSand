#pragma once

#include "Gamefield.h"

struct GLContext {
    uint32_t vertexArrayId;
    uint32_t vertexBufferId;
    uint32_t indexBufferId;
    uint32_t basicShaderId;
    GLFWwindow* window;
    Gamefield* gamefield;
};

void OnUpdate(struct GLContext const* info);