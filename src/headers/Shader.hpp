#ifndef SHADER_H
#define SHADER_H

#include <string>
#include "glad/glad.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader
{
public:
    Shader(std::string vertexShaderPath, std::string fragmentShaderPath);
    ~Shader();
    int getId();
    void use();
    void setUniform1i(std::string, int value);
    void setUniformMat4(std::string, glm::mat4 mtx);

private:
    unsigned int id;
    char *loadShader(std::string path);
    unsigned int compileShader(char *shaderSource, GLenum shader);
};

#endif