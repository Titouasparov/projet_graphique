#include "viewer.h"

#include <iostream>

Viewer::Viewer(int width, int height)
{
    // version hints: create GL window with >= OpenGL 3.3 and core profile
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    win = glfwCreateWindow(width, height, "Viewer", NULL, NULL);

    // make win's OpenGL context current; no OpenGL calls can happen before
    glfwMakeContextCurrent(win);

    // register event handlers
    glfwSetKeyCallback(win, [](GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        Viewer* viewer = static_cast<Viewer*>(glfwGetWindowUserPointer(window));
        viewer->on_key(key);
    });

    // useful message to check OpenGL renderer characteristics
    std::cout << "OpenGL " << glGetString(GL_VERSION) << ", GLSL "
              << glGetString(GL_SHADING_LANGUAGE_VERSION) << ", Renderer "
              << glGetString(GL_RENDERER) << std::endl;

    // initialize GL by setting viewport and default render characteristics
    glClearColor(0.1f, 0.1f, 0.1f, 0.1f);

    // initially empty list of object to draw
    drawables = std::vector<Drawable*>();
}

void Viewer::run()
{
    // Main render loop for this OpenGL window
    while (!glfwWindowShouldClose(win))
    {
        // clear draw buffer
        glClear(GL_COLOR_BUFFER_BIT);

        // draw our scene objects
        for (auto& drawable : drawables)
        {
            drawable->draw();
        }

        // flush render commands, and swap draw buffers
        glfwSwapBuffers(win);

        // Poll for and process events
        glfwPollEvents();
    }
}

void Viewer::add(Drawable* drawable)
{
    // add objects to draw in this window
    drawables.push_back(drawable);
}

void Viewer::on_key(int key)
{
    // 'Q' or 'Escape' quits
    if (key == GLFW_KEY_ESCAPE || key == GLFW_KEY_Q)
    {
        glfwSetWindowShouldClose(win, GLFW_TRUE);
    }

    // Propagate key event to all registered drawables
    for (auto& drawable : drawables)
    {
        drawable->key_handler(key);
    }
}
