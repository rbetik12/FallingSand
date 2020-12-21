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
#include <stdio.h>
#include <Nuklear/nuklear.h>
#include <Nuklear/nuklear_glfw_gl4.h>
#include "../opengl/Shader.h"
#include "../opengl/VertexArray.h"

void OnUpdate(struct GLContext const* info) {
    struct nk_colorf bg;
    bg.r = 0.10f, bg.g = 0.18f, bg.b = 0.24f, bg.a = 1.0f;
    glfwPollEvents();
    nk_glfw3_new_frame();

    if (nk_begin(info->guiContext, "Demo", nk_rect(50, 50, 230, 250),
                 NK_WINDOW_BORDER | NK_WINDOW_MOVABLE | NK_WINDOW_SCALABLE |
                 NK_WINDOW_MINIMIZABLE | NK_WINDOW_TITLE)) {
        enum {
            EASY, HARD
        };
        static int op = EASY;
        static int property = 20;
        nk_layout_row_static(info->guiContext, 30, 80, 1);
        if (nk_button_label(info->guiContext, "button"))
            fprintf(stdout, "button pressed\n");

        nk_layout_row_dynamic(info->guiContext, 30, 2);
        if (nk_option_label(info->guiContext, "easy", op == EASY)) op = EASY;
        if (nk_option_label(info->guiContext, "hard", op == HARD)) op = HARD;

        nk_layout_row_dynamic(info->guiContext, 25, 1);
        nk_property_int(info->guiContext, "Compression:", 0, &property, 100, 10, 1);

        nk_layout_row_dynamic(info->guiContext, 20, 1);
        nk_label(info->guiContext, "background:", NK_TEXT_LEFT);
        nk_layout_row_dynamic(info->guiContext, 25, 1);
        if (nk_combo_begin_color(info->guiContext, nk_rgb_cf(bg), nk_vec2(nk_widget_width(info->guiContext), 400))) {
            nk_layout_row_dynamic(info->guiContext, 120, 1);
            bg = nk_color_picker(info->guiContext, bg, NK_RGBA);
            nk_layout_row_dynamic(info->guiContext, 25, 1);
            bg.r = nk_propertyf(info->guiContext, "#R:", 0, bg.r, 1.0f, 0.01f, 0.005f);
            bg.g = nk_propertyf(info->guiContext, "#G:", 0, bg.g, 1.0f, 0.01f, 0.005f);
            bg.b = nk_propertyf(info->guiContext, "#B:", 0, bg.b, 1.0f, 0.01f, 0.005f);
            bg.a = nk_propertyf(info->guiContext, "#A:", 0, bg.a, 1.0f, 0.01f, 0.005f);
            nk_combo_end(info->guiContext);
        }
    }
    nk_end(info->guiContext);

    BindShader(&info->basicShaderId);
    bool isLeftButtonPressed = IsMousePressed(GLFW_MOUSE_BUTTON_1);
    if (isLeftButtonPressed) {
        MousePos pos;
        struct GLContext* context;
        glfwGetCursorPos(info->window, &pos.x, &pos.y);
        context = glfwGetWindowUserPointer(info->window);
        OnGamefieldClick(context->gamefield, pos);
    }
    OnUpdateGamefield(info->gamefield);
    BindVertexArray(&info->vertexArrayId);

    glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_INT, NULL);

    int width, height;
    glfwGetWindowSize(info->window, &width, &height);
    glViewport(0, 0, width, height);
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0, 0, 0, 1);
    nk_glfw3_render(NK_ANTI_ALIASING_ON);
    glfwSwapBuffers(info->window);
}

