#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include "glad/glad.h"

class Texture
{
private:
    unsigned int id;
    unsigned char *data;
    int width, height, nrChannels, unit = GL_TEXTURE0;
    unsigned char *loadImage(std::string path);
    int type = GL_RGB;

public:
    Texture(std::string path, int unit);
    ~Texture();
    // Binders
    void bind();
    void unbind();
    void activateUnit();
    void deactivateUnit();
    // Getters
    int getId();
    int getUnit();
    // Setters
    void setUnit(int);
    void setType(int);
    // Methods
    void configure();
};

#endif