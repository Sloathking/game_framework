//
// Created by sloath on 10-Sep-26.
//

#include "include/Engine.h"
#include "include/Math.h"
#include "include/Mesh.h"
#include "include/Texture.h"
#include "include/VertexArray.h"
#include <SDL3/SDL_log.h>
#include <fstream>
#include <libs/json.hpp>
#include <iostream>

using json = nlohmann::json;

Mesh::Mesh() = default;

Mesh::~Mesh() = default;

bool Mesh::Load(const std::string& fileName, Engine* game)
{
    std::ifstream file("../../Game/" + fileName);
    if (!file.is_open())
    {
        SDL_Log("Mesh file not found: %s", fileName.c_str());
        return false;
    }

    json meshData{};
    try
    {
        meshData = json::parse(file);
    }
    catch (json::parse_error& e)
    {
        SDL_Log("Error: %s", e.what());
        return false;
    }

    mShaderName = meshData["shader"];

    for (const auto& texture : meshData["textures"])
    {
        auto texName = texture.get<std::string>();
        auto* tex = game->GetTexture(texture);
        if (!tex)
        {
            SDL_Log("Unable to Get Mesh Texture: %s", texName.c_str());
            return false;
        }
        mTextures.emplace_back(tex);
    }

    mSpecPower = meshData["specularPower"];

    // need to flatten the vector<vector<TYPE>> the json gets us
    auto jsonVertices = meshData["vertices"].get<std::vector<std::vector<float>>>();
    std::vector<float> meshVerts;
    // calc radius while we're looking at all the points of the mesh
    for (auto& verts : jsonVertices)
    {
        Vector3 pos{verts[0], verts[1], verts[2]};
        mRadius = Math::Max(mRadius, pos.LengthSq());
        for (float& vert : verts)
        {
            meshVerts.emplace_back(vert);
        }
    }
    mRadius = Math::Sqrt(mRadius);

    auto jsonIndices = meshData["indices"].get<std::vector<std::vector<unsigned int>>>();
    std::vector<unsigned int> meshIndices;
    for (auto& vec : jsonIndices)
        for (unsigned int& index : vec)
            meshIndices.emplace_back(index);

    mVertexAray = new VertexArray(meshVerts.data(), meshVerts.size(),
        meshIndices.data(), meshData["indices"].size());

    return true;
}

void Mesh::Unload()
{
    delete mVertexAray;
    mVertexAray = nullptr;
}

Texture* Mesh::GetTexture(const size_t index) const
{
    if (index < mTextures.size()) return mTextures[index];
    return nullptr;
}
