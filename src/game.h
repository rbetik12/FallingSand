#pragma once

struct GLContext {
    GLFWwindow * window;
};

void OnUpdate(struct GLContext const *info);