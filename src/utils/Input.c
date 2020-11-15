#include <stdio.h>
#include "Input.h"

void OnMouseMove(GLFWwindow* window, double xPos, double yPos) {
    printf("Moved mouse X: %f Y: %f\n", xPos, yPos);
}

void OnMouseClick(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_1) {
        printf("Clicked mouse\n");
    }
}