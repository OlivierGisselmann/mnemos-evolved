#version 410 core

in vec3 vPosition;
in vec3 vNormal;
in vec2 vTexCoords;

void main()
{
    gl_Position = vec4(vPosition, 1.0);
}