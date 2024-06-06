#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>

#include <string>
#include "glm/detail/type_mat4x4.hpp"

/** \brief A graphic program.*/
class Shader {
public:
    /** \brief the shader constructor. Should never be called alone (use loader functions)*/
    Shader(const std::string& vertex_path, const std::string& fragment_path);

    /* \brief Destructor. Destroy the shader component created */
    ~Shader();

    GLuint get_id();

    void use();
    void setMat4(const std::string &name, const glm::mat4 &mat) const;

private:
    GLuint glid;
    GLuint compile_shader(const std::string& path, GLenum shader_type);

};

#endif // SHADER_H
