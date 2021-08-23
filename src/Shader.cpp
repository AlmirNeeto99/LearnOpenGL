#include "headers/Shader.hpp"
#include <fstream>
#include <sstream>
#include <cstring>
#include <iostream>

Shader::Shader(std::string vertexShaderPath, std::string fragmentShaderPath)
{
    // Load the source of the shaders
    char *vertexSource = loadShader(vertexShaderPath);
    char *fragmentSource = loadShader(fragmentShaderPath);
    // Compile the shaders
    unsigned int vertexShader = compileShader(vertexSource, GL_VERTEX_SHADER);
    unsigned int fragmentShader = compileShader(fragmentSource, GL_FRAGMENT_SHADER);

    // Create a shader program
    unsigned int program = glCreateProgram();
    // Attach the shaders
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    // Link the shader program
    glLinkProgram(program);
    // Error handling
    int success;
    char error[512];
    // Get the program linkage status
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    // If fails
    if (!success)
    {
        // Get error and throw exception
        glGetProgramInfoLog(program, 1, NULL, error);
        throw std::runtime_error(error);
    }
    // Delete the shaders
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    this->id = program;
}

char *Shader::loadShader(std::string path)
{
    std::ifstream shader;
    shader.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        shader.open(path);
        std::stringstream shaderStream;
        shaderStream << shader.rdbuf();
        std::string content = shaderStream.str();
        char *code = new char[content.length() - 1];
        const char *c = content.c_str();
        std::strcpy(code, c);
        shader.close();
        return code;
    }
    catch (std::ifstream::failure e)
    {
        throw std::runtime_error("SHADER::ERROR::LOADING");
    }
}

unsigned int Shader::compileShader(char *code, GLenum type)
{
    // Create shader
    unsigned int shader = glCreateShader(type);
    // Copy the source
    glShaderSource(shader, 1, &code, NULL);
    // Error handling
    int success;
    char error[512];
    // Compile
    glCompileShader(shader);
    // Get the compilation status
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    // If fails
    if (!success)
    {
        // Get error and throw exception
        glGetShaderInfoLog(shader, 512, NULL, error);
        throw std::runtime_error(error);
    }
    // Return the newly created shader
    return shader;
}

void Shader::use()
{
    glUseProgram(this->id);
}

Shader::~Shader()
{
    glDeleteProgram(this->id);
}

int Shader::getId()
{
    return this->id;
}
void Shader::setUniform1i(char *name, int value)
{
    glUniform1i(glGetUniformLocation(this->id, name), value);
}