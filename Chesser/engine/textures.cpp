#include "textures.h"

#define STB_IMAGE_IMPLEMENTATION
#include "vendor/stb_image.h"

Textures::Texture::Texture(std::string file, int tex_id) {

        stbi_set_flip_vertically_on_load(true);
        unsigned char * tempData = stbi_load(file.c_str(), &x, &y, &n, 0);
        if (tempData == nullptr) {
            THROW_ERROR(state, "Failed to load texture: " + file);
        }
        else Log::info("Loaded texture: " + file);

        glGenTextures(1, &mTex);
        glBindTexture(GL_TEXTURE_2D, mTex);

        // Give textures a voxel look - optional
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        // Match texture data format to the image we loaded
        GLuint texDataFormat = 0;
        if (n == 3)
        	texDataFormat = GL_RGB;        
        else if (n == 4)
        	texDataFormat = GL_RGBA;

        // Send the image to OpenGL
        glTexImage2D(GL_TEXTURE_2D, 0, texDataFormat, x, y, 0, texDataFormat, GL_UNSIGNED_BYTE, tempData);

        // Go back to the default texture
        glBindTexture(GL_TEXTURE_2D, 0);
        // Free stbi data
        stbi_image_free((void *)tempData);
}