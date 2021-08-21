#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>

void framebuffer_resize(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

char *loadShader(std::string file)
{
    std::ifstream shader;
    shader.open(file);   // Open the file
    std::string line;    // Current line string
    std::string content; // Final content
    // While there's text in file
    while (!shader.eof())
    {
        // Read one line of the file
        std::getline(shader, line);
        // Add the current line to the final content
        content += line + "\n";
    }
    // Closes the file
    shader.close();
    // Create a result string that will be returned
    char *result = new char[content.length() - 1];
    // Copy the content of one string to another, this is necessary because the value were being lost
    std::strcpy(result, content.c_str());
    return result;
}
// Triangle's vertices
GLfloat vertices[] = {
    .0f, .5f, .0f,
    .5f, -.5f, .0f,
    -.5f, -.5f, .0f};

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

    GLFWwindow *window = glfwCreateWindow(800, 600, "Learn OpenGL", NULL, NULL);
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

    // Load the content of vertex shader
    char *vertexShaderSource = loadShader("../src/shaders/vertex.vert");

    unsigned int vertexShader;
    // Create a vertex shader
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    // Copy the vertex shader source
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    // Compile the shader
    glCompileShader(vertexShader);
    // Read the content of fragment shader
    char *fragmentShaderSource = loadShader("../src/shaders/fragment.frag");
    unsigned int fragmentShader;
    // Create a fragment shader
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    // Copy the fragment shader source
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    // Compile the fragment shader
    glCompileShader(fragmentShader);
    // Create a shader program
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    // Attach the vertex shader to program
    glAttachShader(shaderProgram, vertexShader);
    // Attache the fragment shader to program
    glAttachShader(shaderProgram, fragmentShader);
    // Link the program
    glLinkProgram(shaderProgram);
    // Delete the shaders
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    // Enable the attribute at position 0
    glEnableVertexAttribArray(0);

    // Unbind the buffers
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    float time, green;

    while (!glfwWindowShouldClose(window))
    {
        // Clear window
        glClear(GL_COLOR_BUFFER_BIT);
        // Bind the shader program
        glUseProgram(shaderProgram);
        // Bind the VAO
        glBindVertexArray(VAO);
        time = glfwGetTime();
        green = (sin(time) / 2) + .5;
        int pos = glGetUniformLocation(shaderProgram, "color");
        glUniform4f(pos, .5f, green, .5f, 1.0f);
        // Draw the triangle
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgram);
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
