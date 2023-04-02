#include "viewer.h"
#include "triangle.h"
#include "shader.h"
#include <string>

#ifndef SHADER_DIR
#error "SHADER_DIR not defined"
#endif

int main()
{
    // create window, add shaders & scene objects, then run rendering loop
    Viewer viewer;

    // get shader directory
    std::string shader_dir = SHADER_DIR;

    Shader color_shader(shader_dir + "color.vert", shader_dir + "color.frag");
    viewer.add(new Triangle(color_shader));

    viewer.run();              // main function keeps
}