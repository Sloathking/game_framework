//
// Created by sloath on 11-Sep-26.
//

#ifndef MESHCOMPONENT_H
#define MESHCOMPONENT_H

#include "Component.h"
#include <cstddef>

class MeshComponent : public Component
{
public:
    MeshComponent(class Actor3D* owner);
    ~MeshComponent();

    // draw this mesh comp with provided shader
    virtual void Draw(class Shader* shader);

    // set the mesh / tex index used
    virtual void SetMesh(class Mesh* mesh) { mMesh = mesh; }
    void SetTextureIndex(const size_t index) { mTextureIndex = index; }

private:
    Mesh* mMesh{};
    size_t mTextureIndex{};

    Actor3D* mOwner;
};

#endif //MESHCOMPONENT_H
