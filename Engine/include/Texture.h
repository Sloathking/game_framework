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
    void Unload() const;

    void SetActive() const;

    [[nodiscard]] int GetWidth() const { return mWidth; }
    [[nodiscard]] int GetHeight() const { return mHeight; }

private:
    // OpenGL ID of texture
    unsigned int mTexID{0};

    int mWidth{0};
    int mHeight{0};

};

#endif //TEXTURE_H
