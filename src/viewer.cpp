#include "viewer.h"

#include <iostream>
#include <glm/glm.hpp>
#include "glm/ext.hpp"
#include <glm/gtc/matrix_transform.hpp>

Viewer::Viewer(int width, int height)
{
    // Initialize camera parameters
    camera_position = glm::vec3(0.0f, 0.0f, 3.0f);
    camera_front = glm::vec3(0.0f, 0.0f, -1.0f);
    camera_up = glm::vec3(0.0f, 1.0f, 0.0f);
    camera_speed = 0.05f;
    camera_yaw = -90.0f;
    camera_pitch = 0.0f;

    if (!glfwInit())    // initialize window system glfw
    {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        glfwTerminate();
    }

    // version hints: create GL window with >= OpenGL 3.3 and core profile
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    
    win = glfwCreateWindow(width, height, "Viewer", NULL, NULL);

    if (win == NULL) {
        std::cerr << "Failed to create window" << std::endl;
        glfwTerminate();
    }

    // make win's OpenGL context current; no OpenGL calls can happen before
    glfwMakeContextCurrent(win);

    if (glewInit() != GLEW_OK)
    {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        glfwTerminate();
    }

    // Set user pointer for GLFW window to this Viewer instance
    glfwSetWindowUserPointer(win, this);
    // Lock the mouse inside the window
    glfwSetInputMode(win, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // register event handlers
    glfwSetKeyCallback(win, key_callback_static);
    glfwSetCursorPosCallback(win, mouse_callback_static); // Add this line

    // useful message to check OpenGL renderer characteristics
    std::cout << glGetString(GL_VERSION) << ", GLSL "
              << glGetString(GL_SHADING_LANGUAGE_VERSION) << ", Renderer "
              << glGetString(GL_RENDERER) << std::endl;

    // initialize GL by setting viewport and default render characteristics
    glClearColor(0.1f, 0.1f, 0.1f, 0.1f);

    /* tell GL to only draw onto a pixel if the shape is closer to the viewer
    than anything already drawn at that pixel */
    glEnable( GL_DEPTH_TEST ); /* enable depth-testing */
    /* with LESS depth-testing interprets a smaller depth value as meaning "closer" */
    glDepthFunc( GL_LESS );

    // initialize our scene_root
    scene_root = new Node();
}

void Viewer::run()
{
    // Main render loop for this OpenGL window
    while (!glfwWindowShouldClose(win))
    {
        process_input();
        // clear draw buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 model = glm::mat4(1.0f);

        // Use glm::lookAt to create a view matrix from the camera vectors
        glm::mat4 view = glm::lookAt(camera_position, camera_position + camera_front, camera_up);

        glm::mat4 projection = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 10.0f);

        scene_root->draw(model, view, projection);

        // Poll for and process events
        glfwPollEvents();

        // flush render commands, and swap draw buffers
        glfwSwapBuffers(win);
    }

    /* close GL context and any other GLFW resources */
    glfwTerminate();
}

void Viewer::key_callback_static(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    Viewer* viewer = static_cast<Viewer*>(glfwGetWindowUserPointer(window));
    viewer->on_key(key);
}

void Viewer::on_key(int key)
{
    // 'Q' or 'Escape' quits
    if (key == GLFW_KEY_ESCAPE || key == GLFW_KEY_Q)
    {
        glfwSetWindowShouldClose(win, GLFW_TRUE);
    }
}

void Viewer::update_camera_vectors() {
    glm::vec3 front;
    front.x = cos(glm::radians(camera_yaw)) * cos(glm::radians(camera_pitch));
    front.y = sin(glm::radians(camera_pitch));
    front.z = sin(glm::radians(camera_yaw)) * cos(glm::radians(camera_pitch));
    camera_front = glm::normalize(front);

}

void Viewer::process_input() {
// Camera movement
    if (glfwGetKey(win, GLFW_KEY_W) == GLFW_PRESS)
        camera_position += camera_speed * camera_front;
    if (glfwGetKey(win, GLFW_KEY_S) == GLFW_PRESS)
        camera_position -= camera_speed * camera_front;
    if (glfwGetKey(win, GLFW_KEY_A) == GLFW_PRESS)
        camera_position -= glm::normalize(glm::cross(camera_front, camera_up)) * camera_speed;
    if (glfwGetKey(win, GLFW_KEY_D) == GLFW_PRESS)
        camera_position += glm::normalize(glm::cross(camera_front, camera_up)) * camera_speed;

    // Camera rotation (example)
    if (glfwGetKey(win, GLFW_KEY_LEFT) == GLFW_PRESS)
        camera_yaw -= camera_speed;
    if (glfwGetKey(win, GLFW_KEY_RIGHT) == GLFW_PRESS)
        camera_yaw += camera_speed;

    // Update camera vectors after modifying yaw or pitch
    update_camera_vectors();
}

void Viewer::mouse_callback_static(GLFWwindow *window, double xpos, double ypos) {
    Viewer* viewer = static_cast<Viewer*>(glfwGetWindowUserPointer(window));
    viewer->on_mouse(xpos, ypos);
}

void Viewer::on_mouse(double xpos, double ypos) {
    if (first_mouse_movement) {
        last_mouse_x = xpos;
        last_mouse_y = ypos;
        first_mouse_movement = false;
    }

    float xoffset = xpos - last_mouse_x;
    float yoffset = last_mouse_y - ypos; // reversed since y-coordinates go from bottom to top

    last_mouse_x = xpos;
    last_mouse_y = ypos;

    xoffset *= sensitivity;
    yoffset *= sensitivity;

    camera_yaw += xoffset;
    camera_pitch += yoffset;

    // Make sure that when pitch is out of bounds, screen doesn't get flipped
    if (camera_pitch > 89.0f)
        camera_pitch = 89.0f;
    if (camera_pitch < -89.0f)
        camera_pitch = -89.0f;

    // Update camera vectors after modifying yaw or pitch
    update_camera_vectors();
}
