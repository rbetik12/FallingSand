#pragma once

#include "../game/PixelType.h"

typedef struct GLFWwindow GLFWwindow;
struct GLFWwindow;

typedef struct MousePos MousePos;

struct MousePos{
    double x;
    double y;
};

void OnMouseMove(GLFWwindow* window, double xPos, double yPos);
void OnMouseButtonEvent(GLFWwindow* window, int button, int action, int mods);
void OnKeyEvent(GLFWwindow *window, int key, int scancode, int action, int mods);
PixelType GetCurrentPixelType();
