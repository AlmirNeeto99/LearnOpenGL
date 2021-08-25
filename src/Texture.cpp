#include "headers/Texture.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Texture::Texture(std::string path, int unit)
{
    this->data = this->loadImage(path);
    this->unit = unit;
    glGenTextures(1, &this->id);
    glActiveTexture(this->unit);
    glBindTexture(GL_TEXTURE_2D, this->id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, this->width, this->height, 0, GL_RGB, GL_UNSIGNED_BYTE, this->data);
    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);
}

unsigned char *Texture::loadImage(std::string path)
{
    return stbi_load(path.c_str(), &this->width, &this->height, &this->nrChannels, 0);
}

void Texture::unbind()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::bind()
{
    glBindTexture(GL_TEXTURE_2D, this->id);
}

void Texture::useUnit()
{
    glActiveTexture(this->unit);
}

void Texture::setUnit(int unit)
{
    this->unit = unit;
}

int Texture::getId()
{
    return this->id;
}

int Texture::getUnit()
{
    return this->unit;
}

Texture::~Texture()
{
    stbi_image_free(this->data);
}