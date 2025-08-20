#version 410 core

in vec3 fNormal;
in vec3 fPosition;
in vec2 fTexCoords;

uniform vec3 lightColor;
uniform vec3 lightPosition;
uniform float lightIntensity;

uniform vec3 viewPosition;

uniform vec3 ambient;
uniform vec3 diffuse;
uniform vec3 specular;

out vec4 fragColor;

void main()
{
    // Ambient
    float ambientStrength = 0.1;
    vec3 amb = ambient * ambientStrength * lightColor;

    // Diffuse
    vec3 norm = normalize(fNormal);
    vec3 lightDir = normalize(lightPosition - fPosition);
    float diffStrength = max(dot(norm, lightDir), 0.0);
    vec3 diff = diffuse * diffStrength * lightColor;

    // Specular
    vec3 viewDir = normalize(viewPosition - lightPosition);
    vec3 reflectDir = reflect(-lightDir, norm);
    float specStrength = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 spec = specular * specStrength * lightColor * 0.5;

    // Result
    vec3 result = (amb + diff) * lightIntensity;
    fragColor = vec4(result, 1.0);
}