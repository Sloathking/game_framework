//
// Created by sloath on 11-Sep-26.
//

#include "include/MeshComponent.h"
#include "include/Actor.h"
#include "include/Engine.h"
#include "include/Mesh.h"
#include "include/Renderer3D.h"
#include "include/Shader.h"
#include "include/Texture.h"
#include "include/VertexArray.h"

MeshComponent::MeshComponent(Actor* owner) : Component(owner)
{
    auto* renderer = dynamic_cast<Renderer3D*>(mOwner->GetGame()->GetRenderer());
    renderer->AddMeshComp(this);
}

MeshComponent::~MeshComponent()
{
    auto* renderer = dynamic_cast<Renderer3D*>(mOwner->GetGame()->GetRenderer());
    renderer->RemoveMeshComp(this);
}

// draw this mesh comp with provided shader
void MeshComponent::Draw(Shader* shader)
{
    if (mMesh)
    {
        // set world transform
        shader->SetMatrixUniform("uWorldTransform", mOwner->GetWorldTransform());
        shader->SetFloatUniform("uSpecPower", mMesh->GetSpecPower());
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

void MeshComponent::SetMesh(Mesh* mesh)
{
    auto* renderer = dynamic_cast<Renderer3D*>(mOwner->GetGame()->GetRenderer());
    mMesh = mesh;
    const std::string shaderName = mMesh->GetShaderName();
    renderer->SetShaderName(shaderName, this);
}