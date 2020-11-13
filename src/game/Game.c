#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Game.h"
#include "../opengl/Shader.h"
#include "../opengl/VertexArray.h"

void OnUpdate(struct GLContext const* info) {
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0, 0, 0, 1);

    BindShader(&info->basicShaderId);
    OnUpdateGamefield(info->gamefield);
    BindVertexArray(&info->vertexArrayId);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);

    glfwSwapBuffers(info->window);
    glfwPollEvents();
}

