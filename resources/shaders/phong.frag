#version 410 core

in vec3 fNormal;
in vec3 fPosition;
in vec2 fTexCoords;

uniform vec3 lightColor;
uniform vec3 lightPosition;
uniform float lightIntensity;

uniform float lightConstant;
uniform float lightLinear;
uniform float lightQuadratic;

uniform vec3 viewPosition;

uniform vec3 ambientColor;
uniform vec3 diffuseColor;
uniform vec3 specularColor;
uniform float specularStrength;

out vec4 fragColor;

void main()
{
    // Ambient
    float ambientStrength = 0.1;
    vec3 ambient = ambientColor * ambientStrength;

    // Diffuse
    vec3 norm = normalize(fNormal);
    vec3 lightDir = normalize(-lightPosition - fPosition);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diffuseColor * diff;

    // Specular
    vec3 viewDir = normalize(fPosition - viewPosition);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), specularStrength);
    vec3 specular = specularColor * spec * 0.5;

    // Attenuation
    float distance = length(lightPosition - fPosition);
    float attenuation = 1.0 / (lightConstant + lightLinear * distance + lightQuadratic * (distance * distance));  

    // Result
    vec3 result = (ambient + diffuse + specular) * attenuation * lightColor * lightIntensity;

    // Gamma correction
    fragColor = vec4(result, 1.0);
    //fragColor.rgb = pow(fragColor.rgb, vec3(1.0/2.2));
}