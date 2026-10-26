//
// Created by sloath on 11-Sep-26.
//

#ifndef MESHCOMPONENT_H
#define MESHCOMPONENT_H

#include "Component3D.h"
#include "Mesh.h"

class MeshComponent : public Component3D
{
public:
    explicit MeshComponent(Actor3D* owner);
    ~MeshComponent() override;

    // draw this mesh comp with provided shader
    virtual void Draw(class Shader* shader);

    // set the mesh / tex index used
    virtual void SetMesh(class Mesh* mesh);
    void SetTextureIndex(const size_t index) { mTextureIndex = index; }

    // getters / setters
    [[nodiscard]] bool GetVisible() const { return mVisible; }
    void SetVisible(const bool visible) { mVisible = visible; }

    [[nodiscard]] const std::string& GetMeshShaderName() const { return mMesh->GetShaderName(); }

private:
    bool mVisible{true};
    Mesh* mMesh{};
    size_t mTextureIndex{};

};

#endif //MESHCOMPONENT_H
