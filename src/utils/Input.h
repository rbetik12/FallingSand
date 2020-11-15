#pragma once

typedef struct GLFWwindow GLFWwindow;
struct GLFWwindow;

typedef struct MousePos MousePos;

struct MousePos{
    double x;
    double y;
};

void OnMouseMove(GLFWwindow* window, double xPos, double yPos);
void OnMouseClick(GLFWwindow* window, int button, int action, int mods);
