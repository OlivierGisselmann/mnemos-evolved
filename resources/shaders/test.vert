#version 410 core

in vec3 vPosition;
in vec3 vNormal;
in vec2 vTexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 fNormal;
out vec3 fPosition;
out vec2 fTexCoords;

void main()
{
    gl_Position = projection * view * model * vec4(vPosition, 1.0);
    fNormal = mat3(transpose(inverse(model))) * vNormal;
    fPosition = vec3(model * vec4(vPosition, 1.0));
    fTexCoords = vTexCoords;
}