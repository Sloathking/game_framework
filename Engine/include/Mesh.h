//
// Created by sloath on 10-Sep-26.
//

#ifndef MESH_H
#define MESH_H

#include <vector>
#include <string>

class Mesh
{
public:
    Mesh();
    ~Mesh();

    bool Load(const std::string& fileName, class Renderer* renderer);
    void Unload();

    // getters
    [[nodiscard]] class VertexArray* GetVertexArray() const { return mVertexAray; }

    [[nodiscard]] class Texture* GetTexture(size_t index) const;

    [[nodiscard]] const std::string& GetShaderName() const { return mShaderName; }

    [[nodiscard]] float GetRadius() const { return mRadius; }

private:
    std::vector<Texture*> mTextures;

    VertexArray* mVertexAray{};

    // name of shader specified by Mesh
    std::string mShaderName;

    // stores object space bounding sphere radius
    float mRadius{0.0f};

    // specular power of surface
    float mSpecPower;

};


#endif //MESH_H
