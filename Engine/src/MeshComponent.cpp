//
// Created by sloath on 11-Sep-26.
//

#include "include/MeshComponent.h"
#include "include/Actor3D.h"
#include "include/Engine.h"
#include "include/Mesh.h"
#include "include/Renderer.h"
#include "include/Shader.h"
#include "include/Texture.h"
#include "include/VertexArray.h"

MeshComponent::MeshComponent(Actor3D* owner) : Component(owner), mOwner(owner)
{
    mOwner->GetGame()->GetRenderer()->AddMeshComp(this);
}

MeshComponent::~MeshComponent()
{
    mOwner->GetGame()->GetRenderer()->RemoveMeshComp(this);
}

// draw this mesh comp with provided shader
void MeshComponent::Draw(Shader* shader)
{
    if (mMesh)
    {
        // set world transform
        shader->SetMatrixUniform("uWorldTransform", mOwner->GetWorldTransform());
        // set the active texture
        Texture* tex = mMesh->GetTexture(mTextureIndex);
        if (tex) tex->SetActive();
        // set the mesh's vertex array as active
        VertexArray* vertArray = mMesh->GetVertexArray();
        vertArray->SetActive();
        // draw
        glDrawElements(GL_TRIANGLES, vertArray->GetNumIndices(), GL_UNSIGNED_INT, nullptr);
    }
}