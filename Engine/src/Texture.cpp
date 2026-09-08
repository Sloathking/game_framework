//
// Created by sloath on 08-Sep-26.
//

#include "include/Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include <libs/stb_image.h>
#include <GL/glew.h>
#include <SDL3/SDL_log.h>

Texture::Texture()
{

}

Texture::~Texture()
{

}

bool Texture::Load(const std::string& fileName)
{
    int channels = 0;
    const std::string fullPath = "../../Game/" + fileName;
    unsigned char* image = stbi_load(fullPath.c_str(), &mWidth, &mHeight, &channels, 0);
    if (!image)
    {
        SDL_Log("stb_image failed to load image: %s | Error: %s", fileName.c_str(), stbi_failure_reason());
        return false;
    }

    int format = GL_RGB;
    if (channels == 4) format = GL_RGBA;

    glGenTextures(1, &mTexID);
    glBindTexture(GL_TEXTURE_2D, mTexID);
    glTexImage2D(GL_TEXTURE_2D, 0, format, mWidth, mHeight, 0, format, GL_UNSIGNED_BYTE, image);
    stbi_image_free(image);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    return true;
}

void Texture::Unload()
{
    glDeleteTextures(1, &mTexID);
}

void Texture::SetActive()
{
    glBindTexture(GL_TEXTURE_2D, mTexID);
}