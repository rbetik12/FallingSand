#include <GLFW/glfw3.h>
#include "game.h"

void OnUpdate(struct GLContext const* info) {
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.4, 0.1, 0.5, 1);


    glfwSwapBuffers(info->window);
    glfwPollEvents();
}

