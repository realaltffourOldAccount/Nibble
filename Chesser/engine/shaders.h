#ifndef SHADERS_H
#define SHADERS_H

#include "chsr_api.h"

namespace Shaders {

static std::map<std::string, GLuint> mShaderPrograms;

static void CreateProgram(const std::string& shaderName,
                          const std::string& vsFileName,
                          const std::string& fsFileName) {
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;

    vShaderFile.open(vsFileName);
    if (vShaderFile.is_open() == false) {
        THROW_ERROR(state,
                    "Error Occured Reading Vertex Shader File: " + vsFileName);
    } else
        Log::trace("Read Vertex Shader File: " + vsFileName);

    fShaderFile.open(fsFileName);
    if (fShaderFile.is_open() == false) {
        THROW_ERROR(
            state, "Error Occured Reading Fragment Shader File: " + fsFileName);
    } else
        Log::trace("Read Fragment Shader File: " + fsFileName);

    std::stringstream vstream, fstream;
    vstream << vShaderFile.rdbuf();
    fstream << fShaderFile.rdbuf();
    vShaderFile.close();
    fShaderFile.close();

    vertexCode = vstream.str();
    fragmentCode = fstream.str();
    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();

    unsigned int vertex, fragment;
    int success;
    char infoLog[512];

    // vertex shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);

    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        THROW_ERROR(state, "Vertex Shader for Program: " + shaderName +
                               " failed.\n" + std::string(infoLog));
    } else
        Log::trace("Vertex Shader for Program: " + shaderName + " succeeded.");

    // fragment shader
    fragment = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);

    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragment, 512, NULL, infoLog);
        THROW_ERROR(state, "Fragment Shader for Program: " + shaderName +
                               " failed.\n" + std::string(infoLog));
    } else
        Log::trace("Fragment Shader for Program: " + shaderName +
                   " succeeded.");

    // shader program
    GLuint program = glCreateProgram();
    glAttachShader(program, vertex);
    glAttachShader(program, fragment);
    glLinkProgram(program);

    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        THROW_ERROR(state, "Compilation for Program: " + shaderName +
                               " failed.\n" + std::string(infoLog));
    } else
        Log::trace("Compilation for Program: " + shaderName + " succeeded.");

    glDeleteShader(vertex);
    glDeleteShader(fragment);

    mShaderPrograms[shaderName] = program;
}

static const GLuint get(const std::string& name) { mShaderPrograms.at(name); }

static void clean() {
    std::map<std::string, GLuint>::iterator i;
    for (i = mShaderPrograms.begin(); i != mShaderPrograms.end(); i++) {
        GLuint pr = i->second;
        glDeleteShader(pr);
    }
    mShaderPrograms.clear();
}

};  // namespace Shaders

#endif