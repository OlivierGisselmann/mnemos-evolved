#version 410 core

in vec3 fColor;
in vec2 fTexCoords;

out vec4 fragColor;

void main()
{
    fragColor = vec4(fColor, 1.0);
}