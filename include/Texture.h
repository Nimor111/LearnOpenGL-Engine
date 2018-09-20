#ifndef TEXTURE_H
#define TEXTURE_H

#include <iostream>

#include "../include/stb_image.h"
#include <glad/glad.h>

class Texture {
public:
    GLuint id;
    GLenum dimension;

    Texture(const GLchar*, bool, GLenum, GLenum);

    void activateTextureUnit(GLenum);
    void bindTexture();
};

Texture::Texture(const GLchar* texturePath, bool isAlpha, GLenum textureWrappingMode, GLenum dimension)
{
    int width, height, nrChannels;

    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(texturePath, &width, &height, &nrChannels, 0);

    if (data) {
        GLuint texture;

        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, textureWrappingMode);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, textureWrappingMode);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        GLenum imageDataType = isAlpha ? GL_RGBA : GL_RGB;
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, imageDataType, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        stbi_image_free(data);

        glBindTexture(GL_TEXTURE_2D, 0);

        this->id = texture;
        this->dimension = dimension;
    } else {
        std::cout << "Failed to load image data!" << std::endl;
    }
}

void Texture::activateTextureUnit(GLenum textureUnit)
{
    glActiveTexture(textureUnit);
}

void Texture::bindTexture()
{
    glBindTexture(this->dimension, this->id);
}

#endif
