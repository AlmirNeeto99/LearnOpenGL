#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include "../src/headers/Shader.hpp"
#include "../src/headers/Texture.hpp"
#include "stb_image.h"

void framebuffer_resize(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}
// Triangle's vertices
GLfloat vertices[] = {
    -.5f, .5f, .0f, .3f, .5f, .1f, .0f, 1.f,     // Top left
    .5f, .5f, .0f, .6f, .6f, .9f, 1.f, 1.f,      // Top right
    .5f, -.5f, .0f, .9f, .75f, .15f, 1.f, .0f,   // Bottom right
    -.5f, -.5f, .0f, .15f, .3f, .84f, .0f, .0f}; // Bottom left

unsigned int indexes[] = {
    0, 1, 3, // First triangle
    1, 2, 3  // Second triangle
};

int main(int argc, char const *argv[])
{
    if (glfwInit() != GLFW_TRUE)
    {
        std::cout << "Failed to initialize GLFW" << std::endl;
        return -1;
    }
    // Set the OpenGL context version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // Disable window resize button
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    GLFWwindow *window = glfwCreateWindow(800, 600, "LearnOpenGL - Two Textures", NULL, NULL);
    if (!window)
    {
        std::cout << "Unable to create Window" << std::endl;
        return -1;
    }
    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    // Set the Open GL viewport
    glViewport(0, 0, 800, 600);
    // Set the clear color
    glClearColor(.3f, .3f, .3f, 1.f);
    glfwSetFramebufferSizeCallback(window, framebuffer_resize);
    Shader *shader = NULL;
    try
    {
        shader = new Shader("../resources/shaders/textures/vertex.vert", "../resources/shaders/two-textures/fragment.frag");
    }
    catch (const std::exception &ex)
    {
        std::cerr << ex.what() << std::endl;
        return -1;
    }

    unsigned int VAO;
    // Create a new VertexArrayBuffer
    glGenVertexArrays(1, &VAO);

    unsigned int VBO;
    // Generate one buffer
    glGenBuffers(1, &VBO);

    unsigned int EBO;
    // Generate one buffer
    glGenBuffers(1, &EBO);

    // Bind the VertexArrayBuffer
    glBindVertexArray(VAO);
    // Bind GL_ARRAY_BUFFER to VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // Copy the vertices data to GPU
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // Bind GL_ELEMENT_ARRAY_BUFFER to EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    // Copy the indexes to GPU
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexes), indexes, GL_STATIC_DRAW);
    // Set the attributes of the vertices
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void *)0);
    // Enable the attribute at position 0
    glEnableVertexAttribArray(0);
    // Set vertex color attributes
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void *)(3 * sizeof(GLfloat)));
    // Enable the attribute at position 1
    glEnableVertexAttribArray(1);
    // Set texture coordinates attributes
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void *)(6 * sizeof(GLfloat)));
    // Enable the attribute at position 2
    glEnableVertexAttribArray(2);
    // Variables to keep imagem information

    Texture wall("../resources/textures/wall.jpg", GL_TEXTURE0);
    wall.activateUnit();
    wall.bind();
    wall.configure();
    wall.unbind();
    stbi_set_flip_vertically_on_load(true);
    Texture face("../resources/textures/awesomeface.png", GL_TEXTURE1);
    face.setType(GL_RGBA);
    face.activateUnit();
    face.bind();
    face.configure();
    face.unbind();

    // Unbind the buffers
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    while (!glfwWindowShouldClose(window))
    {
        // Clear window
        glClear(GL_COLOR_BUFFER_BIT);
        // Bind the shader program
        wall.activateUnit();
        wall.bind();
        face.activateUnit();
        face.bind();
        shader->use();
        shader->setUniform1i("texture1", 0);
        shader->setUniform1i("texture2", 1);
        // Bind the VAO
        glBindVertexArray(VAO);
        // Draw the triangle
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    //glDeleteTextures(1, &texture);
    delete shader;
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
