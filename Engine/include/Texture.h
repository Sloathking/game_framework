//
// Created by sloath on 08-Sep-26.
//

#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>

class Texture
{
public:
    Texture();
    ~Texture();

    bool Load(const std::string& fileName);
    void Unload();

    void SetActive();

    [[nodiscard]] int GetWidth() const { return mWidth; }
    [[nodiscard]] int GetHeight() const { return mHeight; }

private:
    // OpenGL ID of texture
    unsigned int mTexID;

    int mWidth;
    int mHeight;

};


#endif //TEXTURE_H
