#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 vColor;
layout (location = 2) in mat4 fullTransformMatrix;

out vec3 outColor;

void main()
{
    gl_Position = fullTransformMatrix * vec4(position, 1.0);
    outColor = vColor;
};