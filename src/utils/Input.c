#include "Input.h"
#include "../game/Gamefield.h"
#include "../game/Game.h"
#include <stdio.h>
#include <GLFW/glfw3.h>

static PixelType currentPixelType = Sand;
static bool isMouseButton1Pressed = false;
static uint8_t pixelsRadius = 2;
static bool isUiUsed = false;

void OnMouseMove(GLFWwindow* window, double xPos, double yPos) {
    printf("Moved mouse X: %f Y: %f\n", xPos, yPos);
}

void OnMouseButtonEvent(GLFWwindow* window, int button, int action, int mods) {
    if (isUiUsed) return;
    if (button == GLFW_MOUSE_BUTTON_1 && action == GLFW_PRESS) {
        isMouseButton1Pressed = true;
    }
    else if (button == GLFW_MOUSE_BUTTON_1 && action == GLFW_RELEASE) {
        isMouseButton1Pressed = false;
    }
}

uint8_t GetCurrentPixelsRadius() {
    return pixelsRadius;
}

void OnKeyEvent(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_W && action == GLFW_PRESS) {
        currentPixelType = Water;
    }
    else if (key == GLFW_KEY_S && action == GLFW_PRESS) {
        currentPixelType = Sand;
    }
    else if (key == GLFW_KEY_T && action == GLFW_PRESS) {
        currentPixelType = Stone;
    }
    else if (key == GLFW_KEY_C && action == GLFW_PRESS) {
        struct GLContext* updateInfo = glfwGetWindowUserPointer(window);
        ClearGamefield(updateInfo->gamefield);
    }
    else if (key == GLFW_KEY_P && action == GLFW_PRESS) {
        currentPixelType = Plant;
    }
    else if (key == GLFW_KEY_M && action == GLFW_PRESS) {
        currentPixelType = Smoke;
    }
    else if (key == GLFW_KEY_F && action == GLFW_PRESS) {
        currentPixelType = Fire;
    }
    else if (key == GLFW_KEY_KP_ADD && action == GLFW_PRESS) {
        pixelsRadius += 1;
    }
    else if (key == GLFW_KEY_KP_SUBTRACT && action == GLFW_PRESS) {
        pixelsRadius -= 1;
    }
    printf("Button\n");
}

bool IsMousePressed(int buttonCode) {
    if (buttonCode == GLFW_MOUSE_BUTTON_1) {
        return isMouseButton1Pressed;
    }
    return false;
}

PixelType GetCurrentPixelType() {
    return currentPixelType;
}

void SetCurrentPixelType(PixelType pixelType) {
    currentPixelType = pixelType;
}

void SetUiUse(bool isUsed) {
    isUiUsed = isUsed;
}

bool IsUiUsed() {
    return isUiUsed;
}