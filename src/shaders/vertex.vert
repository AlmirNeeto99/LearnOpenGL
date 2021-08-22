#version 450 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

uniform float offset;

out vec3 ourColor;

void main(){
    vec4 p = vec4(aPos, 1.0);
    p.x += offset;
    gl_Position = p;
    ourColor = aColor;
}