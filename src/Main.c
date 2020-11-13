#include <stdlib.h>
#include <stdio.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Config.h"
#include "Game.h"
#include "VertexArray.h"

uint32_t vertexArrayId;
uint32_t vertexBufferId;
uint32_t indexBufferId;

float verticesSquare[4 * 4] = {
        -1.f, -1.f, 0.0f, 0.0f,
        1.f, -1.f, 1.0f, 0.0f,
        1.f, 1.f, 1.0f, 1.0f,
        -1.f, 1.f, 0.0f, 1.0f
};

uint32_t squareIndices[6] = {
        0, 1, 2,
        2, 3, 0
};

void GLAPIENTRY GLErrorCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message,
                                const void* userParam) {
    fprintf(stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
            (type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""),
            type, severity, message);
}

void InitDebug() {
    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(GLErrorCallback, NULL);
}

void InitBuffers() {
    InitVertexArray(&vertexArrayId);
}

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
    int status = gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
    glfwSwapInterval(1);

    if (!status) {
        printf("Failed to initialize glad!");
        return -1;
    }

    printf("Vendor: %s\n", glGetString(GL_VENDOR));
    printf("Renderer: %s\n", glGetString(GL_RENDERER));
    printf("Version: %s\n", glGetString(GL_VERSION));

    if (glfwWindowShouldClose(window)) {
        fprintf(stderr, "Unexpected window close!\n");
        return -1;
    }

    // Initializes all buffers and debug functions
    InitBuffers();
    InitDebug();

    struct GLContext* updateInfo = malloc(sizeof(struct GLContext));
    updateInfo->window = window;

    while (!glfwWindowShouldClose(window)) {
        OnUpdate(updateInfo);
    }

    free(updateInfo);
    glfwTerminate();
    return 0;
}
