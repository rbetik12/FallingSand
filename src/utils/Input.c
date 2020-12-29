#include "Input.h"
#include <GLFW/glfw3.h>
#include <stdio.h>

static PixelType currentPixelType = Sand;
static bool isMouseButton1Pressed = false;
static uint8_t pixelsRadius = 2;
static bool isUiUsed = false;

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

void SetPixelsRadius(uint8_t r) {
    pixelsRadius = r;
}

void OnKeyEvent(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_EQUAL && action == GLFW_PRESS) {
        pixelsRadius += 1;
    }
    else if (key == GLFW_KEY_MINUS && action == GLFW_PRESS) {
        pixelsRadius -= 1;
    }
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