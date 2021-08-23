#ifndef SHADER_H
#define SHADER_H

#include <string>
#include "glad/glad.h"

class Shader
{
public:
    Shader(std::string vertexShaderPath, std::string fragmentShaderPath);
    ~Shader();
    int getId();
    void use();
    void setUniform1i(char *name, int value);

private:
    unsigned int id;
    char *loadShader(std::string path);
    unsigned int compileShader(char *shaderSource, GLenum shader);
};

#endif