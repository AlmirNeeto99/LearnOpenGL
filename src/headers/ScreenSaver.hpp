#ifndef SCREENSAVER_H

#define SCREENSAVER_H
#include "GLFW/glfw3.h"
#include <vector>
#include <string>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

class ScreenSaver
{
private:
public:
    static void print(GLFWwindow *window)
    {
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        GLsizei nrChannels = 3;
        GLsizei stride = nrChannels * width;
        stride += (stride % 4) ? (4 - stride % 4) : 0;
        GLsizei bufferSize = stride * height;
        std::vector<char> buffer(bufferSize);
        glPixelStorei(GL_PACK_ALIGNMENT, 4);
        glReadBuffer(GL_FRONT);
        glReadPixels(0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, buffer.data());
        stbi_flip_vertically_on_write(true);
        srand(0);
        int r = time(0);
        std::string a = std::to_string(r) + ".png";
        const char *c = a.c_str();
        stbi_write_png(c, width, height, nrChannels, buffer.data(), stride);
    }
};

#endif