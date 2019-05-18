#include "Texture.h"

#ifndef __EMSCRIPTEN__
#define STB_IMAGE_IMPLEMENTATION
#endif
#include "vendor/stb_image.h"

GEngine::Texture::Texture(std::string file, GLuint tex_id) {
    stbi_set_flip_vertically_on_load(true);
    unsigned char* imgData = stbi_load(file.c_str(), &this->_imgWidth,
                                       &this->_imgHeight, &this->_imgComp, 0);
    if (imgData == nullptr) {
        THROW_ERROR("Failed to load texture: " + file);
        __err_check();
    } else
        Log::info("Loaded Texture: " + file);

    GLCall(glGenTextures(1, &this->_tex_id));
    GLCall(glBindTexture(GL_TEXTURE_2D, this->_tex_id));

    // Optional texture settings
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

    // Match texture data format to the image we load
    GLuint texDataFormat = 0;
    if (this->_imgComp == 3)
        texDataFormat = GL_RGB;
    else if (this->_imgComp == 4)
        texDataFormat = GL_RGBA;

    // Send image data to OpenGL
    GLCall(glTexImage2D(GL_TEXTURE_2D, 0, texDataFormat, this->_imgWidth,
                        this->_imgHeight, 0, texDataFormat, GL_UNSIGNED_BYTE,
                        imgData));

    GLCall(glGenerateMipmap(GL_TEXTURE_2D));

    GLCall(glBindTexture(GL_TEXTURE_2D, 0));
    // Free stbi image data
    stbi_image_free((void*)imgData);
}

GEngine::Texture::~Texture(void) { this->destroy(); }

void GEngine::Texture::bind(int index) {
    GLCall(glActiveTexture(GL_TEXTURE0 + index));
    GLCall(glBindTexture(GL_TEXTURE_2D, this->_tex_id));
}

void GEngine::Texture::unbind(void) {
    GLCall(glBindTexture(GL_TEXTURE_2D, this->_tex_id));
}

int GEngine::Texture::getImgWidth(void) { return this->_imgWidth; }

int GEngine::Texture::getImgHieght(void) { return this->_imgHeight; }

int GEngine::Texture::getImgCompNum(void) { return this->_imgComp; }

void GEngine::Texture::destroy(void) {
    GLCall(glDeleteTextures(1, &this->_tex_id));
}