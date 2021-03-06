#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include "../src/headers/Shader.hpp"
#include "../src/headers/Texture.hpp"
#include "../src/headers/Camera.hpp"
#include "stb_image.h"
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

glm::vec3 position = glm::vec3(0, 0, 3);
glm::vec3 direction = glm::vec3(0, 0, -1);
glm::vec3 up = glm::vec3(0, 1, 0);
float last = .0f, delta = 0.0f, current;
glm::mat4 view = glm::mat4(1.0);

void handle_key(GLFWwindow *window, int key, int scancode, int action, int mode)
{
    if (GLFW_KEY_ESCAPE == key && GLFW_PRESS == action)
    {
        glfwSetWindowShouldClose(window, true);
    }
}

void framebuffer_resize(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

GLfloat simpleCube[] = {
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
    0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
    0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
    0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
    -0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,

    -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
    0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
    0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
    0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
    -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
    -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,

    -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f,
    -0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f,
    -0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f,
    -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f,

    0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f,
    0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
    0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
    0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
    0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f,
    0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f,

    -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,
    0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,
    0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f,
    0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f,
    -0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,

    -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
    0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
    0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
    0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
    -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
    -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f};

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

    GLFWwindow *window = glfwCreateWindow(800, 600, "LearnOpenGL - Lightning", NULL, NULL);
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
    glClearColor(.0f, .0f, .0f, 1.f);
    // Enabling depth test so faces won't overlap
    glEnable(GL_DEPTH_TEST);
    glfwSetFramebufferSizeCallback(window, framebuffer_resize);
    glfwSetKeyCallback(window, handle_key);
    Shader *shader = NULL;
    Shader *lightShader = NULL;
    try
    {
        shader = new Shader("../resources/shaders/lightning/vertex.vert", "../resources/shaders/lightning/fragment.frag");
        lightShader = new Shader("../resources/shaders/lightning/vertex.vert", "../resources/shaders/lightning/lamp.frag");
    }
    catch (const std::exception &ex)
    {
        std::cerr << ex.what() << std::endl;
        return -1;
    }

    unsigned int simpleCubeVAO, simpleCubeVBO;
    glGenBuffers(1, &simpleCubeVBO);
    glGenVertexArrays(1, &simpleCubeVAO);

    glBindVertexArray(simpleCubeVAO);
    glBindBuffer(GL_ARRAY_BUFFER, simpleCubeVBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(simpleCube), simpleCube, GL_DYNAMIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void *)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void *)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, simpleCubeVBO);
    glBindVertexArray(0);

    glm::mat4 model = glm::mat4(1.0), projection = glm::mat4(1.0);
    projection = glm::perspective(glm::radians(45.0f), 800.f / 600.f, .1f, 1000.f);
    shader->use();
    shader->setUniformMat4("projection", projection);
    lightShader->use();
    lightShader->setUniformMat4("projection", projection);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    Camera c(vec3(0, 15, 30), vec3(0, -15, -30));
    glm::vec4 lightPos(0, 5.0, 0.0, 1.0);
    while (!glfwWindowShouldClose(window))
    {
        current = glfwGetTime();
        delta = current - last;
        last = current;
        // Clear window
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // Draw cube
        glBindVertexArray(simpleCubeVAO);
        lightShader->use();
        model = glm::mat4(1.0);
        model = glm::rotate(model, glm::radians((float)glfwGetTime() * 25), glm::vec3(1.0, 0, 0));
        model = glm::translate(model, vec3(0, 5, 0));
        model = glm::scale(model, vec3(.2, .2, .2));
        lightPos = model * lightPos;
        lightShader->setUniformMat4("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        Shader::unbind();
        shader->use();
        shader->setUniformVec3("objectColor", vec3(1.0, 0.5, .4));
        shader->setUniformVec3("lightColor", vec3(1.0, 1.0, 1.0));
        shader->setUniformVec3("lightPos", lightPos);
        shader->setUniformVec3("viewPos", c.getPosition());
        model = glm::mat4(1.0);
        shader->setUniformMat4("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        // Swap Buffer and handle events
        glfwSwapBuffers(window);
        glfwPollEvents();
        view = c.update(window);
        // Update views
        lightShader->use();
        lightShader->setUniformMat4("view", view);
        shader->use();
        shader->setUniformMat4("view", view);
    }
    glDeleteVertexArrays(1, &simpleCubeVAO);
    glDeleteBuffers(1, &simpleCubeVBO);
    delete shader;
    delete lightShader;
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
