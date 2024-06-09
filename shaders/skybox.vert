#version 330 core
layout (location = 0) in vec3 aPos;

out vec3 TexCoords;

uniform mat4 projection;
uniform mat4 view;

void main()
{
    // Remove the translation from the view matrix
    mat4 view_no_translation = mat4(mat3(view));

    vec4 pos = projection * view_no_translation * vec4(aPos, 1.0);
    gl_Position = pos.xyww;
    TexCoords = aPos;
}