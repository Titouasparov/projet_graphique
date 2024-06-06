#ifndef VIEWER_H
#define VIEWER_H

#include <vector>
#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "shader.h"
#include "node.h"
#include "Skybox.h"

class Viewer {
public:
    Viewer(int width=640, int height=480);

    void run();
    void on_key(int key);

    Node *scene_root;
    Skybox *skybox;

private:
    GLFWwindow* win;
    static void key_callback_static(GLFWwindow* window, int key, int scancode, int action, int mods);
    // Camera parameters
    glm::vec3 camera_position;
    glm::vec3 camera_front;
    glm::vec3 camera_up;
    float camera_speed;
    float camera_yaw;
    float camera_pitch;
    // Variables pour le contrôle des mouvements de la caméra avec la souris
    bool first_mouse_movement = true;
    float last_mouse_x = 0.0f;
    float last_mouse_y = 0.0f;
    float sensitivity = 0.1f; // Sensibilité de la souris


    void update_camera_vectors();
    void process_input();
    static void mouse_callback_static(GLFWwindow* window, double xpos, double ypos);
    void on_mouse(double xpos, double ypos);

};

#endif // VIEWER_H
