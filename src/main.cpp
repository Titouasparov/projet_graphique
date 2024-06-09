#include "viewer.h"
#include "textured_sphere.h"
#include "lighting_sphere.h"
#include "texture.h"
#include "node.h"
#include "shader.h"
#include "Skybox.h"
#include <string>


#ifndef SHADER_DIR
#error "SHADER_DIR not defined"
#endif

#ifndef TEXTURE_DIR
#error "TEXTURE_DIR not defined"
#endif

int main()
{
    // create window, add shaders & scene objects, then run rendering loop
    Viewer viewer;

    // get shader directory
    std::string shader_dir = SHADER_DIR;

    Shader *texture_shader = new Shader(shader_dir + "texture.vert", shader_dir + "texture.frag");

    // get textures directory
    std::string texture_dir = TEXTURE_DIR;
    Shader *phong_shader = new Shader(shader_dir + "phong.vert", shader_dir + "phong.frag");
    // Créer un tableau de textures pour faciliter l'accès
    Texture* planet_textures[8] = {
            new Texture(texture_dir + "mercury.jpg"),
            new Texture(texture_dir + "venus.jpg"),
            new Texture(texture_dir + "earth.jpg"),
            new Texture(texture_dir + "mars.jpg"),
            new Texture(texture_dir + "jupiter.jpg"),
            new Texture(texture_dir + "saturn.jpg"),
            new Texture(texture_dir + "uranus.jpg"),
            new Texture(texture_dir + "neptune.jpg")
    };

    // Créer le soleil
    Texture* sun_texture = new Texture(texture_dir + "sun.jpg");
    Shape* sun = new TexturedSphere(texture_shader, sun_texture);
    // Positionner le soleil près du barycentre
    glm::mat4 sun_mat = glm::translate(glm::mat4(1.0f), glm::vec3(0.2f, 0.0f, 0.0f))
                        * glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f))
                        * glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));


    Node* sun_node = new Node(sun_mat);

    sun_node->add(sun);
    viewer.scene_root->add(sun_node);




// Créer les planètes
    for (int i = 0; i < 8; i++) {
        Shape* planet = new TexturedSphere(texture_shader, planet_textures[i]);
        float angle = i * 45.0f; // Positionner les planètes autour du soleil à des angles différents

        // Définir les demi-axes de l'ellipse pour chaque planète
        float a = 2.0f + 0.5f * i; // Ces valeurs sont arbitraires, vous pouvez les ajuster en fonction de vos besoins
        float b = 1.5f + 0.3f * i; // Ces valeurs sont arbitraires, vous pouvez les ajuster en fonction de vos besoins

        // Calculer la position de la planète sur l'ellipse
        glm::vec3 position = glm::vec3(a * cos(glm::radians(angle)), 0.0f, b * sin(glm::radians(angle)));

        glm::mat4 planet_mat = glm::translate(glm::mat4(1.0f), position)
                               * glm::scale(glm::mat4(1.0f), glm::vec3(0.5f, 0.5f, 0.5f)) // Les planètes sont plus petites que le soleil
                               * glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        Node* planet_node = new Node(planet_mat);
        planet_node->add(planet);
        viewer.scene_root->add(planet_node);


    }


    viewer.run();
}