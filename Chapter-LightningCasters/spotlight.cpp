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
#include "../src/headers/ScreenSaver.hpp"

glm::vec3 position = glm::vec3(0, 0, 3);
glm::vec3 direction = glm::vec3(0, 0, -1);
glm::vec3 up = glm::vec3(0, 1, 0);
float last = .0f, delta = 0.0f, current;
glm::mat4 view = glm::mat4(1.0);
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

GLfloat simpleCube[] = {
    // positions          // normals           // texture coords
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
    0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f,
    0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
    0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
    -0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,

    -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
    0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
    0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
    0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
    -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
    -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,

    -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
    -0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
    -0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
    -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,

    0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
    0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
    0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
    0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
    0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
    0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f,
    0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
    0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
    -0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,

    -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
    0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
    0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
    0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
    -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
    -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f};

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

    GLFWwindow *window = glfwCreateWindow(1080, 720, "LearnOpenGL - LightningCasters", NULL, NULL);
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
    glViewport(0, 0, 1080, 720);
    // Set the clear color
    glClearColor(.0f, .0f, .0f, 1.f);
    // Enabling depth test so faces won't overlap
    glEnable(GL_DEPTH_TEST);
    glfwSetFramebufferSizeCallback(window, framebuffer_resize);
    glfwSetKeyCallback(window, handle_key);
    Shader *shader = NULL;
    try
    {
        shader = new Shader("../resources/shaders/lightning-casters/vertex.vert", "../resources/shaders/lightning-casters/spotlight.frag");
    }
    catch (const std::exception &ex)
    {
        std::cerr << ex.what() << std::endl;
        return -1;
    }

    Texture diff("../resources/textures/container2.png", GL_TEXTURE0);
    Texture spec("../resources/textures/container2_specular.png", GL_TEXTURE1);

    diff.activateUnit();
    diff.bind();
    diff.setType(GL_RGBA);
    diff.configure();
    diff.unbind();
    diff.deactivateUnit();

    spec.activateUnit();
    spec.bind();
    spec.setType(GL_RGBA);
    spec.configure();
    spec.unbind();
    spec.deactivateUnit();

    unsigned int simpleCubeVAO, simpleCubeVBO;
    glGenBuffers(1, &simpleCubeVBO);
    glGenVertexArrays(1, &simpleCubeVAO);

    glBindVertexArray(simpleCubeVAO);
    glBindBuffer(GL_ARRAY_BUFFER, simpleCubeVBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(simpleCube), simpleCube, GL_DYNAMIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void *)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void *)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void *)(6 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, simpleCubeVBO);
    glBindVertexArray(0);

    glm::mat4 model = glm::mat4(1.0), projection = glm::mat4(1.0);
    projection = glm::perspective(glm::radians(45.0f), 1080.f / 720.f, .1f, 1000.f);
    shader->use();
    shader->setUniformMat4("projection", projection);
    // Material
    shader->setUniform1i("material.diffuse", 0);
    shader->setUniform1i("material.specular", 1);
    shader->setUniform1f("material.shininess", 32.f);
    // Light color
    shader->setUniformVec3("light.ambient", glm::vec3(0.2f, 0.2f, 0.2f));
    shader->setUniformVec3("light.diffuse", glm::vec3(0.5f, 0.5f, 0.5f)); // darken diffuse light a bit
    shader->setUniformVec3("light.specular", glm::vec3(1.0f, 1.0f, 1.0f));
    shader->setUniform1f("light.cutOff", glm::cos(glm::radians(12.5)));

    glm::vec3 positions[15] = {
        {8, .1f, 9}, {-1, 6, 3}, {7, 5, 8}, {-6, 3, 7}, {5, 7, 1}, {-4, 6, -1}, {3, 5, 7}, {-3, 3, 4}, {9, 5, -6}, {-6, 7, 3}, {-6, -2, -7}, {-7, 5, 7}, {1, 2, 7}, {-3, -7, 4}, {6, -6, 8}};

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
        glBindVertexArray(simpleCubeVAO);
        shader->use();
        shader->setUniformVec3("viewPos", c.getPosition());
        model = glm::mat4(1.0);
        shader->setUniformMat4("model", model);
        // Applying diffuse texture
        diff.activateUnit();
        diff.bind();
        // Applying specular texture
        spec.activateUnit();
        spec.bind();
        // Draw cubes
        for (int i = 0; i < 15; i++)
        {
            model = glm::mat4(1.0);
            model = glm::translate(model, positions[i]);
            shader->setUniformMat4("model", model);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        diff.unbind();
        diff.deactivateUnit();
        spec.unbind();
        spec.deactivateUnit();
        // Swap Buffer and handle events
        glfwSwapBuffers(window);
        glfwPollEvents();
        view = c.update(window);
        // Update views
        shader->use();
        shader->setUniformVec3("light.direction", c.getDirection());
        shader->setUniformVec3("light.position", c.getPosition());
        shader->setUniformMat4("view", view);
    }
    glDeleteVertexArrays(1, &simpleCubeVAO);
    glDeleteBuffers(1, &simpleCubeVBO);
    delete shader;
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
