//
// Created by sloath on 07-Sep-26.
//

#include "../include/Shader.h"
#include <SDL3/SDL_log.h>
#include <fstream>
#include <sstream>

#include "include/Math.h"

Shader::Shader() = default;

Shader::~Shader() = default;

bool Shader::Load(const std::string& vertName, const std::string& fragName)
{
    // compile vert and frag shaders
    if (!CompileShader(vertName, GL_VERTEX_SHADER, mVertexShader)or
        !CompileShader(fragName, GL_FRAGMENT_SHADER, mFragShader))
    {
        return false;
    }

    // now create the shader program
    mShaderProgram = glCreateProgram();
    glAttachShader(mShaderProgram, mVertexShader);
    glAttachShader(mShaderProgram, mFragShader);
    glLinkProgram(mShaderProgram);

    // verify that the program is linked successfully
    if (!IsValidProgram()) return false;

    return true;
}

void Shader::SetActive()
{
    glUseProgram(mShaderProgram);
}

bool Shader::CompileShader(const std::string& fileName, GLenum shaderType, GLuint& outShader)
{
    // open file
    std::string fullPath = "../../Game/Shaders/" + fileName;
    if (std::ifstream shaderFile(fullPath); shaderFile.is_open())
    {
        // read all the test into a string
        std::stringstream sstream;
        sstream << shaderFile.rdbuf();
        std::string contents = sstream.str();
        const char* contentsChar = contents.c_str();

        // create a shader of the specified type
        outShader = glCreateShader(shaderType);

        // set the source chars and try to compile
        glShaderSource(outShader, 1, &(contentsChar), nullptr);
        glCompileShader(outShader);
        if (!IsCompiled(outShader))
        {
            SDL_Log("Failed to compile shader %s!", fileName.c_str());
            return false;
        }
    }
    else
    {
        SDL_Log("Shader file not found: %s", fileName.c_str());
        return false;
    }

    return true;
}

bool Shader::IsCompiled(const GLuint shader)
{
    GLint status;

    // query the compile status
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if (status != GL_TRUE)
    {
        char buffer[512] = {};
        glGetShaderInfoLog(shader, 511, nullptr, buffer);
        SDL_Log("GLSL Compile Failed: \n%s", buffer);
        return false;
    }

    return true;
}

bool Shader::IsValidProgram()
{
    GLint status;

    glGetProgramiv(mShaderProgram, GL_LINK_STATUS, &status);
    if (status != GL_TRUE)
    {
        char buffer[512] = {};
        glGetProgramInfoLog(mShaderProgram, 511, nullptr, buffer);
        SDL_Log("Invalid Program!\n%s", buffer);
        return false;
    }

    return true;
}

void Shader::Unload()
{
    glDeleteProgram(mShaderProgram);
    glDeleteShader(mVertexShader);
    glDeleteShader(mFragShader);
}

void Shader::SetMatrixUniform(const std::string& name, const Matrix4& matrix)
{
    // find the uniform by this name
    GLint loc = glGetUniformLocation(mShaderProgram, name.c_str());

    // send the matrix data to the uniform
    glUniformMatrix4fv(loc, 1, GL_TRUE, matrix.GetAsFloatPtr());
}