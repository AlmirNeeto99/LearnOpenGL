#version 450 core

out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main(){
    // The "reversing" here is tricky... It works because the X coordinates will be 0 or 1
    // Basically, this code make 0 = 1 and 1 = 0, for the X
    FragColor = mix(texture2D(texture1, TexCoord), texture2D(texture2, vec2(1.0 - TexCoord.x, TexCoord.y)), 0.5);
}