#include <stdio.h>
#include "Debug.h"

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