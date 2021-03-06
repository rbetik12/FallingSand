#include <stdlib.h>
#include <stdio.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_STANDARD_VARARGS
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT
#define NK_IMPLEMENTATION
#define NK_GLFW_GL3_IMPLEMENTATION
#define NK_KEYSTATE_BASED_INPUT

#include <Nuklear/nuklear.h>
#include <Nuklear/nuklear_glfw_gl3.h>

#include "utils/Config.h"
#include "game/Game.h"
#include "opengl/VertexArray.h"
#include "opengl/Buffer.h"
#include "utils/Debug.h"
#include "opengl/Shader.h"
#include "game/Gamefield.h"
#include "utils/Input.h"
#include "utils/AudioManager.h"

uint32_t vertexArrayId;
uint32_t vertexBufferId;
uint32_t indexBufferId;
uint32_t basicShaderId;
Gamefield* gamefield;
GLFWwindow* window;

float verticesSquare[5 * 4] = {
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
    glEnable(GL_DEPTH_TEST);
    const char* basicVertexShader = ""
                                    "#version 330 core"
                                    "\n"
                                    "layout(location = 0) in vec3 position;"
                                    "layout(location = 1) in vec2 texCoord;"
                                    ""
                                    "out vec2 v_TexCoord;"
                                    ""
                                    "void main() {"
                                    "   gl_Position = vec4(position.xy, -1, 1.0);"
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
//    InitDebug();
    InitGame();
    InitEventHandlers();

    struct GLContext* updateInfo = malloc(sizeof(struct GLContext));
    updateInfo->window = window;
    updateInfo->vertexArrayId = vertexArrayId;
    updateInfo->indexBufferId = indexBufferId;
    updateInfo->basicShaderId = basicShaderId;
    updateInfo->gamefield = gamefield;

    AudioManagerPlaySoundOnce(Ambient);

    struct nk_context* ctx;
    struct nk_glfw glfw = {0};
    ctx = nk_glfw3_init(&glfw, window, NK_GLFW3_DEFAULT);
    updateInfo->guiContext = ctx;
    updateInfo->glfw = &glfw;

    {
        struct nk_font_atlas* atlas;
        nk_glfw3_font_stash_begin(&glfw, &atlas);
        nk_glfw3_font_stash_end(&glfw);
    }

    glfwSetWindowUserPointer(window, updateInfo);

    while (!glfwWindowShouldClose(window)) {
        OnUpdate(updateInfo);
    }

    nk_glfw3_shutdown(&glfw);
    free(updateInfo);
    glfwTerminate();
    return 0;
}
