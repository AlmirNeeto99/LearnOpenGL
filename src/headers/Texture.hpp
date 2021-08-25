#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include "glad/glad.h"

class Texture
{
private:
    unsigned int id;
    unsigned char *data;
    int width, height, nrChannels, unit;
    unsigned char *loadImage(std::string path);

public:
    Texture(std::string path, int unit);
    ~Texture();
    // Binders
    void bind();
    void unbind();
    void useUnit();
    // Getters
    int getId();
    int getUnit();
    // Setters
    void setUnit(int);
};

#endif