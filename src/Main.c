#include <stdlib.h>
#include <stdio.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Config.h"
#include "Game.h"
#include "VertexArray.h"
#include "Buffer.h"
#include "Debug.h"
#include "Shader.h"

uint32_t vertexArrayId;
uint32_t vertexBufferId;
uint32_t indexBufferId;
uint32_t basicShaderId;

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

void InitBuffers() {
    InitVertexBuffer(&vertexBufferId, verticesSquare, sizeof(verticesSquare));
    InitIndexBuffer(&indexBufferId, squareIndices, sizeof(squareIndices));

    InitVertexArray(&vertexArrayId);
    AddVertexBuffer(&vertexArrayId, &vertexBufferId);
    AddIndexBuffer(&vertexArrayId, &indexBufferId);
}

void InitShaders() {
    const char* basicVertexShader = ""
                                    "#version 330 core"
                                    "\n"
                                    "layout(location = 0) in vec3 position;"
                                    "layout(location = 0) in vec2 texCoord;"
                                    ""
                                    "out vec2 v_TexCoord;"
                                    ""
                                    "void main() {"
                                    "   gl_Position = vec4(position, 1.0);"
                                    "   v_TexCoord = texCoord;"
                                    "}";

    const char* basicFragmentShader = ""
                                      "#version 330 core"
                                      "\n"
                                      "layout(location = 0) out vec4 color;"
                                      ""
                                      "in vec2 v_TexCoord;"
                                      "uniform sampler2D u_Texture;"
                                      ""
                                      "void main() {"
                                      " vec4 texColor = vec4(1.0, 0.0, 0.0, 0.0);"
                                      " color = texColor;"
                                      "}";

    InitShader(&basicShaderId, basicVertexShader, basicFragmentShader);
    BindShader(&basicShaderId);
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
    InitShaders();
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
