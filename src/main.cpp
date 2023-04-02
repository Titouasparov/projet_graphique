#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "viewer.h"
#include "triangle.h"
#include "shader.h"

#include <iostream>

int main()
{
    // create window, add shaders & scene objects, then run rendering loop
    glfwInit();                // initialize window system glfw

    Viewer viewer;

    Shader color_shader("color.vert", "color.frag");
    viewer.add(new Triangle(color_shader));

    viewer.run();              // main function keeps
}