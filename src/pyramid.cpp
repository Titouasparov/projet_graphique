#include "pyramid.h"

#include "GLFW/glfw3.h"
#include <glm/glm.hpp>
#include "glm/ext.hpp"
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

Pyramid::Pyramid(Shader *shader_program) : shader_program_(shader_program->get_id()) 
{
    // Pyramid vertex positions
    GLfloat vertex_buffer_data[] = {
        // base
        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,
        // top
         0.0f,  0.5f,  0.0f
    };

    // Pyramid indices
    GLint indices[] = {
        // base
        0, 1, 2,
        2, 3, 0,
        // sides
        0, 4, 1,
        1, 4, 2,
        2, 4, 3,
        3, 4, 0
    };

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(2, &buffers[0]);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data), vertex_buffer_data, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

    // Index buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
}

void Pyramid::draw()
{
    glUseProgram(this->shader_program_);
    glBindVertexArray(VAO);
    float rotation = glm::radians(45.0f + 40*glfwGetTime());
    glm::mat4 rot_mat = glm::rotate(glm::mat4(1.0f), rotation, glm::vec3(0, 1, 0));
    glm::mat4 tra_mat = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f));
    glm::mat4 sca_mat = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f));
    glm::mat4 proj_mat = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 10.0f);

    GLint loc = glGetUniformLocation(this->shader_program_, "view");
    glm::mat4 view = tra_mat * rot_mat * sca_mat;
    glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(view));

    loc = glGetUniformLocation(this->shader_program_, "projection");
    glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(proj_mat));

    glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_INT, 0);
}

Pyramid::~Pyramid() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &buffers[0]);
}

void Pyramid::key_handler(int key) {
    return;
}
