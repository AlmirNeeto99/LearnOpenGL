#version 450 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 ourColor;

void main(){
    vec4 x = vec4(aPos, 1.0);
    x.y = x.y * -1;
    gl_Position = x;
    ourColor = aColor;
}