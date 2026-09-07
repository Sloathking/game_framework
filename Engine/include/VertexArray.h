//
// Created by sloath on 07-Sep-26.
//

#ifndef VERTEXARRAY_H
#define VERTEXARRAY_H


class VertexArray
{
public:
    VertexArray(const float* verts, unsigned int numVerts, const unsigned int* indices, unsigned int numIndices);
    ~VertexArray();

    // Activate this vertex array (so we cand raw it)
    void SetActive();

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


#endif //VERTEXARRAY_H
