#include <stdio.h>
#include <glfw/include/GLFW/glfw3.h>
#include "Input.h"
#include "../game/Game.h"

static PixelType currentPixelType = Sand;

void OnMouseMove(GLFWwindow* window, double xPos, double yPos) {
    printf("Moved mouse X: %f Y: %f\n", xPos, yPos);
}

void OnMouseButtonEvent(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_1 && action == GLFW_PRESS) {
        MousePos pos;
        struct GLContext * context;
        glfwGetCursorPos(window, &pos.x, &pos.y);
        context = glfwGetWindowUserPointer(window);
        OnGamefieldClick(context->gamefield, pos);
    }
}

void OnKeyPress(GLFWwindow * window, uint32_t keycode) {
    if (keycode == GLFW_KEY_W) {

    }
    else if (keycode == GLFW_KEY_S) {
        printf("S is pressed!\n");
        currentPixelType = Sand;
    }
}

void OnKeyEvent(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_W && action == GLFW_PRESS) {
        printf("W is pressed!\n");
        currentPixelType = Water;
    }
    else if (key == GLFW_KEY_S && action == GLFW_PRESS) {
        printf("S is pressed!\n");
        currentPixelType = Sand;
    }
}

PixelType GetCurrentPixelType() {
    return currentPixelType;
}