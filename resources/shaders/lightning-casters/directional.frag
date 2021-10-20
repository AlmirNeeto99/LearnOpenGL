#version 450 core

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

struct DirectionalLight {
    vec4 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;

out vec4 FragColor;

uniform vec3 viewPos;

uniform Material material;
uniform DirectionalLight light;

void main(){
    vec3 norm = normalize(Normal);
    vec3 lightDir, lightVector = vec3(light.direction);
    // If w component is 0 treat as direction light
    if(light.direction.w == 0.0){
        lightDir = normalize(lightVector * -1);
    } else{ // Else, treat as normal light
        lightDir = normalize(lightVector - FragPos);
    }
    // Diffuse lightning
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * vec3(texture2D(material.diffuse, TexCoords));
    // Ambient lightning
    vec3 ambient = light.ambient * vec3(texture2D(material.diffuse, TexCoords));
    // Specular lightning
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec * vec3(texture2D(material.specular, TexCoords));
    // Apply color
    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);
}