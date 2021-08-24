#version 450 core

out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;

uniform float opacity;

void main(){
    FragColor = mix(texture2D(texture1, TexCoord), texture2D(texture2, TexCoord), opacity) * vec4(ourColor, 1.0);
}