#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>

/** \brief A graphic program.*/
class Shader {
public:
    /** \brief the shader constructor. Should never be called alone (use loader functions)*/
    Shader(const char* vertex_source, const char* fragment_source);

    /* \brief Destructor. Destroy the shader component created */
    ~Shader();

    GLuint get_id();

private:
    GLuint glid;
    GLuint compile_shader(const char* src, GLenum shader_type);
};

#endif // SHADER_H
