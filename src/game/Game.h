#pragma once

#include "Gamefield.h"

struct GLContext {
    uint32_t vertexArrayId;
    uint32_t indexBufferId;
    uint32_t basicShaderId;
    GLFWwindow* window;
    Gamefield* gamefield;
    struct nk_context* guiContext;
    struct nk_glfw* glfw;
};

void OnUpdate(struct GLContext const* info);