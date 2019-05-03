#ifndef SHADERS_H
#define SHADERS_H

#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
#include <glm/glm.hpp>

// Shaders standard for uniform attributes
#define SHADER_ATTRIB_POS 0 
#define SHADER_ATTRIB_COLOR 1
#define SHADER_ATTRIB_TEXCOORD 2 // if needed

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
        Log::info("Read Vertex Shader File: " + vsFileName);

    fShaderFile.open(fsFileName);
    if (fShaderFile.is_open() == false) {
        THROW_ERROR(
            state, "Error Occured Reading Fragment Shader File: " + fsFileName);
    } else
        Log::info("Read Fragment Shader File: " + fsFileName);

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
        THROW_ERROR(state, "Compilation of Vertex Shader for Program: " + shaderName +
                               " failed.\n" + std::string(infoLog));
    } else
        Log::info("Compilation of Vertex Shader for Program: " + shaderName + " succeeded.");

    // fragment shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);

    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragment, 512, NULL, infoLog);
        THROW_ERROR(state, "Compilation of Fragment Shader for Program: " + shaderName +
                               " failed.\n" + std::string(infoLog));
    } else
        Log::info("Compilation of Fragment Shader for Program: " + shaderName +
                   " succeeded.");

    // shader program
    GLuint program = glCreateProgram();
    glAttachShader(program, vertex);
    glAttachShader(program, fragment);
    glLinkProgram(program);

    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        THROW_ERROR(state, "Linking for Program: " + shaderName +
                               " failed.\n" + std::string(infoLog));
    } else
        Log::info("Linking for Program: " + shaderName + " succeeded.");

    glDeleteShader(vertex);
    glDeleteShader(fragment);

    mShaderPrograms[shaderName] = program;
}

static const GLuint get(const std::string& name) { return mShaderPrograms.at(name); }

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
