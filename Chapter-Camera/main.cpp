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
float last, delta, current;
glm::mat4 view = glm::mat4(1.0);

float pitch = 0, yaw = 0;
double xPos, yPos, prevX = 300, prevY = 400;

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
/* Cube's vertices
Thanks to LearnOpenGL 

Unfortunately, mapping the textures coordinates would be a hard work to do.
Since it's not purpose right now, i copied the cube coordinates already mapped.

*/
GLfloat vertices[] = {
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
    0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
    0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
    0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
    -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

    -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
    0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
    0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
    0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
    -0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
    -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,

    -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
    -0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
    -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
    -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

    0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
    0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
    0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
    0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
    0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
    0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
    0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
    0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
    0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
    -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

    -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
    0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
    0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
    0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
    -0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
    -0.5f, 0.5f, -0.5f, 0.0f, 1.0f};

unsigned int indexes[] = {
    // Front face
    0, 1, 3,
    1, 2, 3};

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

    GLFWwindow *window = glfwCreateWindow(800, 600, "LearnOpenGL - Camera", NULL, NULL);
    glfwSetWindowPos(window, (1366 - 800) / 2, (800 - 600) / 2);
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
    try
    {
        shader = new Shader("../resources/shaders/coordinate-system/vertex.vert", "../resources/shaders/coordinate-system/fragment.frag");
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

    //unsigned int EBO;
    // Generate one buffer
    //glGenBuffers(1, &EBO);

    // Bind the VertexArrayBuffer
    glBindVertexArray(VAO);
    // Bind GL_ARRAY_BUFFER to VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // Copy the vertices data to GPU
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // Bind GL_ELEMENT_ARRAY_BUFFER to EBO
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    // Copy the indexes to GPU
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexes), indexes, GL_STATIC_DRAW);
    // Set the attributes of the vertices
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void *)0);
    // Enable the attribute at position 0
    glEnableVertexAttribArray(0);
    // Set vertex color attributes
    //glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void *)(3 * sizeof(GLfloat)));
    // Enable the attribute at position 1
    //glEnableVertexAttribArray(1);
    // Set texture coordinates attributes
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void *)(3 * sizeof(GLfloat)));
    // Enable the attribute at position 2
    glEnableVertexAttribArray(2);
    // Variables to keep imagem information

    Texture wooden("../resources/textures/wooden.jpg", GL_TEXTURE0);
    wooden.activateUnit();
    wooden.bind();
    wooden.configure();
    wooden.unbind();
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
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glm::mat4 model = glm::mat4(1.0), projection = glm::mat4(1.0);
    projection = glm::perspective(glm::radians(45.0f), 800.f / 600.f, .1f, 1000.f);

    glm::vec3 cubePositions[] = {
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(2.0f, 5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3(2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f, 3.0f, -7.5f),
        glm::vec3(1.3f, -2.0f, -2.5f),
        glm::vec3(1.5f, 2.0f, -2.5f),
        glm::vec3(1.5f, 0.2f, -1.5f),
        glm::vec3(-1.3f, 1.0f, -1.5f)};
    last = glfwGetTime();
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    Camera c(vec3(0, 0, 3), vec3(0, 0, -1));
    while (!glfwWindowShouldClose(window))
    {
        current = glfwGetTime();
        delta = current - last;
        last = current;
        // Clear window
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // Bind the shader program
        wooden.activateUnit();
        wooden.bind();
        face.activateUnit();
        face.bind();
        shader->use();
        // Bind the VAO
        glBindVertexArray(VAO);
        for (int i = 0; i < sizeof(cubePositions); i++)
        {
            model = glm::mat4(1.f);
            model = glm::translate(model, cubePositions[i]);
            model = glm::rotate(model, glm::radians((float)glfwGetTime() * 50), glm::vec3(1, cubePositions[i].y, cubePositions[i].z));
            shader->setUniform1i("texture1", 0);
            shader->setUniform1i("texture2", 1);
            shader->setUniformMat4("model", model);
            shader->setUniformMat4("view", view);
            shader->setUniformMat4("projection", projection);
            // Draw the Cube
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        // Swap Buffer and handle events
        glfwSwapBuffers(window);
        glfwPollEvents();
        view = c.update(window);
    }
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    //glDeleteBuffers(1, &EBO);
    //glDeleteTextures(1, &texture);
    delete shader;
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
