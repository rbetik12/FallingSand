#include "Game.h"
#include <stdbool.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_STANDARD_VARARGS
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT
#define NK_KEYSTATE_BASED_INPUT

#include <Nuklear/nuklear.h>
#include <Nuklear/nuklear_glfw_gl3.h>
#include <stdio.h>
#include "../opengl/Shader.h"
#include "../opengl/VertexArray.h"

#define MAX_VERTEX_BUFFER 512 * 1024 * 4
#define MAX_ELEMENT_BUFFER 128 * 1024 * 4

void OnUpdate(struct GLContext const* info) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0, 0, 0, 1);
    struct nk_colorf bg;
    bg.r = 0.10f, bg.g = 0.18f, bg.b = 0.24f, bg.a = 1.0f;

    BindShader(&info->basicShaderId);
    bool isLeftButtonPressed = IsMousePressed(GLFW_MOUSE_BUTTON_1);
    if (isLeftButtonPressed) {
        MousePos pos;
        struct GLContext* context;
        glfwGetCursorPos(info->window, &pos.x, &pos.y);
        context = glfwGetWindowUserPointer(info->window);
        OnGamefieldClick(context->gamefield, pos);
    }
    BindGamefield(0, info->gamefield);
    OnUpdateGamefield(info->gamefield);
    BindVertexArray(&info->vertexArrayId);

    glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_INT, NULL);
    UnBindGamefield(info->gamefield);

    nk_glfw3_new_frame(info->glfw);
    static int pixelType;
    if (nk_begin(info->guiContext, "Controls", nk_rect(0, 0, 250, 250),
                 NK_WINDOW_BORDER | NK_WINDOW_TITLE)) {

        nk_layout_row_static(info->guiContext, 20, 100, 1);
        nk_label(info->guiContext, "Pixel types:", NK_TEXT_ALIGN_LEFT);

        nk_layout_row_dynamic(info->guiContext, 30, 2);
        if (nk_option_label(info->guiContext, "Sand", pixelType == Sand)) pixelType = Sand;
        if (nk_option_label(info->guiContext, "Water", pixelType == Water)) pixelType = Water;
        if (nk_option_label(info->guiContext, "Fire", pixelType == Fire)) pixelType = Fire;
        if (nk_option_label(info->guiContext, "Smoke", pixelType == Smoke)) pixelType = Smoke;
        if (nk_option_label(info->guiContext, "Plant", pixelType == Plant)) pixelType = Plant;
        if (nk_option_label(info->guiContext, "Stone", pixelType == Stone)) pixelType = Stone;
        SetCurrentPixelType(pixelType);

        nk_layout_row_static(info->guiContext, 20, 50, 3);
        if (nk_button_label(info->guiContext, "Clear")) {
            ClearGamefield(info->gamefield);
        }

        nk_layout_row_static(info->guiContext, 20, 100, 1);
        nk_label(info->guiContext, "Brush size:", NK_TEXT_ALIGN_LEFT);

        nk_layout_row_static(info->guiContext, 20, 50, 2);
        if (nk_button_label(info->guiContext, "-")) {
            if (GetCurrentPixelsRadius() > 0) {
                SetPixelsRadius(GetCurrentPixelsRadius() - 1);
            }
        }
        if (nk_button_label(info->guiContext, "+")) {
            if (GetCurrentPixelsRadius() < UINT8_MAX) {
                SetPixelsRadius(GetCurrentPixelsRadius() + 1);
            }
        }
    }

    nk_end(info->guiContext);

    int width, height;
    glfwGetWindowSize(info->window, &width, &height);
    glViewport(0, 0, width, height);
    SetUiUse(nk_item_is_any_active(info->guiContext));
    glfwPollEvents();
    nk_glfw3_render(info->glfw, NK_ANTI_ALIASING_ON, MAX_VERTEX_BUFFER, MAX_ELEMENT_BUFFER);
    glfwSwapBuffers(info->window);
}

