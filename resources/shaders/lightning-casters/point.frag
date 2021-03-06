#version 450 core

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

struct PointLight {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadradic;
};

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;

out vec4 FragColor;

uniform vec3 viewPos;

uniform Material material;
uniform PointLight light;

void main(){
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - FragPos);
    float dist = length(light.position - FragPos);
    float attenuation = 1.0 / (light.constant + (dist * light.linear) + ((dist * dist) * light.quadradic));
    // Diffuse lightning
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * vec3(texture2D(material.diffuse, TexCoords)) * attenuation;
    // Ambient lightning
    vec3 ambient = light.ambient * vec3(texture2D(material.diffuse, TexCoords)) * attenuation;
    // Specular lightning
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec * vec3(texture2D(material.specular, TexCoords)) * attenuation;
    // Apply color
    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);
}