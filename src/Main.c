#include <stdlib.h>
#include <stdio.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "utils/Config.h"
#include "game/Game.h"
#include "opengl/VertexArray.h"
#include "opengl/Buffer.h"
#include "utils/Debug.h"
#include "opengl/Shader.h"
#include "game/Gamefield.h"

uint32_t vertexArrayId;
uint32_t vertexBufferId;
uint32_t indexBufferId;
uint32_t basicShaderId;
Gamefield *gamefield;

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
    InitIndexBuffer(&indexBufferId, squareIndices, sizeof(squareIndices) / sizeof(uint32_t));
    InitVertexArray(&vertexArrayId);

    AddVertexBuffer(&vertexArrayId, &vertexBufferId);
    AddIndexBuffer(&vertexArrayId, &indexBufferId);
}

void InitShaders() {
    const char* basicVertexShader = ""
                                    "#version 330 core"
                                    "\n"
                                    "layout(location = 0) in vec3 position;"
                                    "layout(location = 1) in vec2 texCoord;"
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
                                      " vec4 texColor = texture(u_Texture, v_TexCoord);"
                                      " "
                                      " color = texColor;"
                                      "}";

    InitShader(&basicShaderId, basicVertexShader, basicFragmentShader);
    BindShader(&basicShaderId);
    SetUniform1i(&basicShaderId, "u_Texture", 0);
    UnBindShader(&basicShaderId);
}

void InitGame() {
    gamefield = malloc(sizeof(Gamefield));
    InitGamefield(gamefield);
    BindGamefield(0, gamefield);
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
    InitGame();

    struct GLContext* updateInfo = malloc(sizeof(struct GLContext));
    updateInfo->window = window;
    updateInfo->vertexArrayId = vertexArrayId;
    updateInfo->vertexBufferId = vertexBufferId;
    updateInfo->indexBufferId = indexBufferId;
    updateInfo->basicShaderId = basicShaderId;
    updateInfo->gamefield = gamefield;

    while (!glfwWindowShouldClose(window)) {
        OnUpdate(updateInfo);
    }

    free(updateInfo);
    glfwTerminate();
    return 0;
}
