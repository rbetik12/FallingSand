#include <glad/glad.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include "Shader.h"

void InitShader(uint32_t * shaderId, const char* vertexSrc, const char* fragmentSrc) {
    // Create an empty vertex shader handle
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

// Send the vertex shader source code to GL
// Note that std::string's .c_str is NULL character terminated.
    const GLchar* source = vertexSrc;
    glShaderSource(vertexShader, 1, &source, 0);

// Compile the vertex shader
    glCompileShader(vertexShader);

    GLint isCompiled = 0;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
    if (isCompiled == GL_FALSE) {
        GLint maxLength = 0;
        glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

        // The maxLength includes the NULL character
        char * infoLog = malloc(sizeof(char) * maxLength);
        glGetShaderInfoLog(vertexShader, maxLength, &maxLength, infoLog);

        // We don't need the shader anymore.
        glDeleteShader(vertexShader);

        // Use the infoLog as you see fit.

        // In this simple program, we'll just leave
        fprintf(stderr, "%s", infoLog);
        fprintf(stderr, "Vertex shader compilation failed!\n");
        free(infoLog);
        assert(false);
        return;
    }

// Create an empty fragment shader handle
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

// Send the fragment shader source code to GL
// Note that std::string's .c_str is NULL character terminated.
    source = (const GLchar*) fragmentSrc;
    glShaderSource(fragmentShader, 1, &source, 0);

// Compile the fragment shader
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
    if (isCompiled == GL_FALSE) {
        GLint maxLength = 0;
        glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

        // The maxLength includes the NULL character
        char * infoLog = malloc(sizeof(char) * maxLength);
        glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, infoLog);

        // We don't need the shader anymore.
        glDeleteShader(fragmentShader);
        // Either of them. Don't leak shaders.
        glDeleteShader(vertexShader);

        // Use the infoLog as you see fit.

        // In this simple program, we'll just leave
        fprintf(stderr, "%s", infoLog);
        fprintf(stderr, "Fragment shader compilation failed!\n");
        free(infoLog);
        assert(false);
        return;
    }

// Vertex and fragment shaders are successfully compiled.
// Now time to link them together into a program.
// Get a program object.
    *shaderId = glCreateProgram();
    GLuint program = *shaderId;

// Attach our shaders to our program
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);

// Link our program
    glLinkProgram(program);

// Note the different functions here: glGetProgram* instead of glGetShader*.
    GLint isLinked = 0;
    glGetProgramiv(program, GL_LINK_STATUS, (int*) &isLinked);
    if (isLinked == GL_FALSE) {
        GLint maxLength = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

        // The maxLength includes the NULL character
        char * infoLog = malloc(sizeof(char) * maxLength);
        glGetProgramInfoLog(program, maxLength, &maxLength, infoLog);

        // We don't need the program anymore.
        glDeleteProgram(program);
        // Don't leak shaders either.
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        // Use the infoLog as you see fit.

        // In this simple program, we'll just leave
        fprintf(stderr, "%s", infoLog);
        fprintf(stderr, "Shader linking failed!\n");
        free(infoLog);
        assert(false);
        return;
    }

// Always detach shaders after a successful link.
    glDetachShader(program, vertexShader);
    glDetachShader(program, fragmentShader);
}

void BindShader(const uint32_t * shaderId) {
    glUseProgram(*shaderId);
}

void UnBindShader(uint32_t * shaderId) {
    glUseProgram(0);
}

int GetUniformLocation(uint32_t * shaderId, const char* name) {
    int location = glGetUniformLocation(*shaderId, name);
    if (location == -1) {
        fprintf(stderr, "Warning: uniform %s doesn't exist!\n", name);
    }
    return location;
}

void SetUniform1i(uint32_t * shaderId, const char* name, int value) {
    glUniform1i(GetUniformLocation(shaderId, name), value);
}

