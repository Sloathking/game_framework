//
// Created by sloath on 07-Sep-26.
//

#ifndef SPRITEVERTEXARRAY_H
#define SPRITEVERTEXARRAY_H

class SpriteVertexArray
{
public:
    SpriteVertexArray(const float* verts, unsigned int numVerts, const unsigned int* indices, unsigned int numIndices);
    ~SpriteVertexArray();

    // Activate this vertex array (so we cand raw it)
    void SetActive() const;

    [[nodiscard]] unsigned int GetNumIndices() const { return mNumIndices; }
    [[nodiscard]] unsigned int GetNumVerts() const { return mNumVerts; }

private:
    // number of vertices in vertex buffer
    unsigned int mNumVerts;

    // number of indices in the index buffer
    unsigned int mNumIndices;

    // OpenGL ID of vertex buffer
    unsigned int mVertexBuffer;

    // OpenGL ID of index buffer
    unsigned int mIndexBuffer;

    // OpenGL ID of vertex array object
    unsigned int mVertexArray;
};

#endif //SPRITEVERTEXARRAY_H
