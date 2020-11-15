#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include "Game.h"
#include "../opengl/Shader.h"
#include "../opengl/VertexArray.h"

void OnUpdate(struct GLContext const* info) {
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    BindShader(&info->basicShaderId);
    OnUpdateGamefield(info->gamefield);
    BindVertexArray(&info->vertexArrayId);

    glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_INT, NULL);

    glfwSwapBuffers(info->window);
    glfwPollEvents();
}

