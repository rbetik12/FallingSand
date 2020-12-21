#include <stdlib.h>
#include <stdio.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <vx-sound.h>

#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_STANDARD_VARARGS
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT
#define NK_KEYSTATE_BASED_INPUT
#define NK_IMPLEMENTATION
#define NK_GLFW_GL4_IMPLEMENTATION

#include <Nuklear/nuklear.h>
#include <Nuklear/nuklear_glfw_gl4.h>

#include "utils/Config.h"
#include "game/Game.h"
#include "opengl/VertexArray.h"
#include "opengl/Buffer.h"
#include "utils/Debug.h"
#include "opengl/Shader.h"
#include "game/Gamefield.h"
#include "utils/Input.h"
#include "utils/AudioManager.h"

#define MAX_VERTEX_BUFFER 512 * 1024
#define MAX_ELEMENT_BUFFER 128 * 1024

uint32_t vertexArrayId;
uint32_t vertexBufferId;
uint32_t indexBufferId;
uint32_t basicShaderId;
Gamefield* gamefield;
GLFWwindow* window;

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

void InitEventHandlers() {
    glfwSetMouseButtonCallback(window, OnMouseButtonEvent);
    glfwSetKeyCallback(window, OnKeyEvent);
}

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

void InitSound() {
    AudioManagerInit();
}

int main(int argc, char** argv) {
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
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
    InitSound();
    InitBuffers();
    InitShaders();
    InitDebug();
    InitGame();
    InitEventHandlers();

    struct GLContext* updateInfo = malloc(sizeof(struct GLContext));
    updateInfo->window = window;
    updateInfo->vertexArrayId = vertexArrayId;
    updateInfo->indexBufferId = indexBufferId;
    updateInfo->basicShaderId = basicShaderId;
    updateInfo->gamefield = gamefield;

    glfwSetWindowUserPointer(window, updateInfo);

    AudioManagerPlaySoundOnce(Ambient);

    struct nk_context* ctx;
    ctx = nk_glfw3_init(window, NK_GLFW3_DEFAULT, MAX_VERTEX_BUFFER, MAX_ELEMENT_BUFFER);
    updateInfo->guiContext = ctx;

    {
        struct nk_font_atlas* atlas;
        nk_glfw3_font_stash_begin(&atlas);
        nk_glfw3_font_stash_end();
    }


    while (!glfwWindowShouldClose(window)) {
        OnUpdate(updateInfo);
    }

    free(updateInfo);
    glfwTerminate();
    return 0;
}
