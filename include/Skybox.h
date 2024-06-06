#ifndef OPENGLPROGRAM_SKYBOX_H
#define OPENGLPROGRAM_SKYBOX_H

#include "shape.h"
#include "shader.h"
#include <vector>
#include <string>

class Skybox : public Shape {
public:
    Shader* shader;
    GLuint skyboxVAO;
    GLuint cubemapTexture;

    Skybox(Shader* shader, std::vector<std::string> faces);
    void draw(const glm::mat4& view, const glm::mat4& projection);

private:
    GLuint loadCubemap(std::vector<std::string> faces);
};

#endif //OPENGLPROGRAM_SKYBOX_H