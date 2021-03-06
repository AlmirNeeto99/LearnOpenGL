#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include "../src/headers/Shader.hpp"
#include "../src/headers/ScreenSaver.hpp"

bool printing = false;

void handle_key(GLFWwindow *window, int key, int scancode, int action, int mode)
{
    if (GLFW_KEY_ESCAPE == key && GLFW_PRESS == action)
    {
        glfwSetWindowShouldClose(window, true);
    }
    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS && !printing)
    {
        printing = true;
        ScreenSaver::print(window);
    }
    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_RELEASE)
    {
        printing = false;
    }
}

void framebuffer_resize(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}
// Triangle's vertices
GLfloat vertices[] = {
    .0f, .5f, .0f, .85f, .5f, .15f,
    .5f, -.5f, .0f, .13f, .91f, .17f,
    -.5f, -.5f, .0f, .5f, .3f, .7f};

unsigned int indexes[] = {
    0, 1, 2};

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

    GLFWwindow *window = glfwCreateWindow(800, 600, "LearnOpenGL - Shaders", NULL, NULL);
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
    glfwSetKeyCallback(window, handle_key);
    Shader *shader = NULL;
    try
    {
        shader = new Shader("../resources/shaders/shaders/vertex.vert", "../resources/shaders/shaders/fragment.frag");
    }
    catch (const std::exception &ex)
    {
        std::cerr << ex.what() << std::endl;
        return -1;
    }

    unsigned int EBO;
    // Generate one buffer
    glGenBuffers(1, &EBO);

    /* Hello triangle */
    unsigned int VBO;
    // Generate one buffer
    glGenBuffers(1, &VBO);
    unsigned int VAO;
    // Create a new VertexArrayBuffer
    glGenVertexArrays(1, &VAO);
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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void *)0);
    // Enable the attribute at position 0
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void *)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    // Unbind the buffers
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    while (!glfwWindowShouldClose(window))
    {
        // Clear window
        glClear(GL_COLOR_BUFFER_BIT);
        // Bind the shader program
        shader->use();
        // Bind the VAO
        glBindVertexArray(VAO);
        // Draw the triangle
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    // Deleting buffers
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    // Deleting shader
    delete shader;
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
