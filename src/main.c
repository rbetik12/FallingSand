#include <stdlib.h>
#include <GLFW/glfw3.h>
#include "config.h"
#include "game.h"

int main(int argc, char** argv) {
    GLFWwindow* window;

    if (!glfwInit())
        return -1;

    window = glfwCreateWindow(WIDTH, HEIGHT, "Falling sand", NULL, NULL);

    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    struct GLContext* updateInfo = malloc(sizeof(struct GLContext));
    updateInfo->window = window;

    while (!glfwWindowShouldClose(window)) {
        OnUpdate(updateInfo);
    }

    free(updateInfo);
    glfwTerminate();
    return 0;
}
