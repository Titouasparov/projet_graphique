#include "shader.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cstdio>
#include <cstdlib>

using namespace std;

Shader::Shader(const char* vertex_source, const char* fragment_source) {
    GLuint vert_shader, frag_shader;
    GLint status;

    // Create vertex shader
    vert_shader = compile_shader(vertex_source, GL_VERTEX_SHADER);

    // Create fragment shader
    frag_shader = compile_shader(fragment_source, GL_FRAGMENT_SHADER);

    // Create shader program
    glid = glCreateProgram();
    glAttachShader(glid, vert_shader);
    glAttachShader(glid, frag_shader);
    glLinkProgram(glid);

    // Check if shader program linked successfully
    glGetProgramiv(glid, GL_LINK_STATUS, &status);
    if (status != GL_TRUE) {
        char buffer[512];
        glGetProgramInfoLog(glid, 512, NULL, buffer);
        cerr << "Failed to link shader program: " << buffer << endl;
        exit(EXIT_FAILURE);
    }

    // Delete shaders
    glDeleteShader(vert_shader);
    glDeleteShader(frag_shader);
}

Shader::~Shader() {
    glUseProgram(0);
    glDeleteProgram(glid);
}

GLuint Shader::get_id() {
    return glid;
}

GLuint Shader::compile_shader(const char* src, GLenum shader_type) {
    GLuint shader;
    GLint status;
    const GLchar* src_array[1] = {src};

    // Create shader
    shader = glCreateShader(shader_type);
    glShaderSource(shader, 1, src_array, NULL);
    glCompileShader(shader);

    // Check if shader compiled successfully
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if (status != GL_TRUE) {
        char buffer[512];
        glGetShaderInfoLog(shader, 512, NULL, buffer);
        cerr << "Failed to compile shader: " << buffer << endl;
        exit(EXIT_FAILURE);
    }

    return shader;
}
