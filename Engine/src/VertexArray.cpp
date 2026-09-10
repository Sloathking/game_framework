//
// Created by sloath on 07-Sep-26.
//

#include "../include/VertexArray.h"

#include <GL/glew.h>

VertexArray::VertexArray(const float* verts, const unsigned int numVerts,
    const unsigned int* indices, const unsigned int numIndices) : mNumVerts{numVerts}, mNumIndices{numIndices}
{
    /* Things to pass to Buffers:
     *  The active buffer type to write to
     *  Number of bytes to copy
     *  Source to copy from (pointer)
     *  How will we use this data?
     */

    // create vertex array
    glGenVertexArrays(1, &mVertexArray);
    glBindVertexArray(mVertexArray);

    // create vertex buffer
    glGenBuffers(1, &mVertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, numVerts * 8 * sizeof(float), verts, GL_STATIC_DRAW);

    // create index buffer
    glGenBuffers(1, &mIndexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIndices * sizeof(unsigned int), indices, GL_STATIC_DRAW);

    // specify vertex attributes
    /// position is 3 floats
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, nullptr);
    /// normal is 3 floats
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, reinterpret_cast<void*>(sizeof(float) * 3));
    /// text coords 2 foats
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, reinterpret_cast<void*>(sizeof(float) * 6));
}

VertexArray::~VertexArray()
{
    glDeleteBuffers(1, &mVertexBuffer);
    glDeleteBuffers(1, &mIndexBuffer);
    glDeleteVertexArrays(1, &mVertexArray);
}

// Activate this vertex array (so we can draw it)
void VertexArray::SetActive() const
{
    glBindVertexArray(mVertexArray);
}