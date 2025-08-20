#version 410 core

in vec3 fColor;
in vec2 fTexCoords;

uniform vec3 ambient;
uniform vec3 diffuse;
uniform vec3 specular;
uniform float specularStrength;

uniform sampler2D textureMap;

out vec4 fragColor;

void main()
{
    fragColor = vec4(0.6, 0.6, 0.6, 1.0);
}