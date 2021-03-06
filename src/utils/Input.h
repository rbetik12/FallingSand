#pragma once

#include <stdbool.h>
#include <stdint.h>
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
bool IsMousePressed(int buttonCode);
PixelType GetCurrentPixelType();
uint8_t GetCurrentPixelsRadius();
bool IsUiUsed();
void SetUiUse(bool isUsed);
void SetCurrentPixelType(PixelType pixelType);
void SetPixelsRadius(uint8_t radius);
