//
// Created by sloath on 07-Sep-26.
//

#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <string>

class Shader
{
public:
    Shader();
    ~Shader();

    // load the vert/frag shaders with given names
    bool Load(const std::string& vertName, const std::string& fragName);
    void Unload();

    // set value on a Uniform inside a vert / frag
    void SetMatrixUniform(const std::string& name, const class Matrix4& matrix) const;
    void SetVectorUniform(const std::string& name, const class Vector3& vec) const;
    void SetFloatUniform(const std::string& name, const float& val) const;

    // set this as the active shader program
    void SetActive();

private:
    // tries to compile the specified shader
    bool CompileShader(const std::string& fileName, GLenum shaderType, GLuint& outShader);

    // tests whether shader compiled successfully
    static bool IsCompiled(GLuint shader);

    // tests whether vert/frag programs link
    bool IsValidProgram();

    // store the shader obj ID
    GLuint mVertexShader{0};
    GLuint mFragShader{0};
    GLuint mShaderProgram{0};
};

#endif //SHADER_H
