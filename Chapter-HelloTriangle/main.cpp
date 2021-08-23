#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <iostream>
#include "../src/headers/Shader.hpp"

void framebuffer_resize(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

// Triangle vertices
GLfloat vertices[18] = {
    .0f, .5f, .0f, .9f, .1f, .15f,
    .5f, -.5f, .0f, .1f, .8, .94f,
    -.5f, -.5f, .0f, .78f, .4f, .35f};

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

    GLFWwindow *window = glfwCreateWindow(800, 600, "LearnOpenGL - Hello Triangle", NULL, NULL);
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

    Shader *shader = new Shader("../resources/shaders/shaders/vertex.vert", "../resources/shaders/shaders/fragment.frag");

    // Create a Vertex Buffer
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    // Create a VertexArray
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    // VAO must be binded first
    glBindVertexArray(VAO);
    // VBO must be binded after
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void *)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void *)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    while (!glfwWindowShouldClose(window))
    {
        // Clear window
        glClear(GL_COLOR_BUFFER_BIT);
        shader->use();
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    delete shader;
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
