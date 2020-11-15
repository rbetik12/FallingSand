#include <stdio.h>
#include <glfw/include/GLFW/glfw3.h>
#include "Input.h"
#include "../game/Game.h"

void OnMouseMove(GLFWwindow* window, double xPos, double yPos) {
    printf("Moved mouse X: %f Y: %f\n", xPos, yPos);
}

void OnMouseClick(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_1 && action == GLFW_PRESS) {
        MousePos pos;
        struct GLContext * context;
        glfwGetCursorPos(window, &pos.x, &pos.y);
        context = glfwGetWindowUserPointer(window);
        OnGamefieldClick(context->gamefield, pos);
    }
}