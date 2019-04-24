#ifndef TEXTURE_H
#define TEXTURE_H

#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
#include <glm/glm.hpp>
#include "univ_includes.h"

#define STB_IMAGE_IMPLEMENTATION
#include "vendor/stb_image.h"

#include "Rect.h"

namespace Textures {

class Texture {
   public:
    Texture(std::string file, int tex_id = 0) {
        glGenTextures(1, &mTex);
        glBindTexture(GL_TEXTURE_2D, mTex);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        imgData =
            stbi_load(file.c_str(), &imgWidth, &imgHeight, &nrChannels, 0);
        if (imgData) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imgWidth, imgHeight, 
                         0, GL_RGB, GL_UNSIGNED_BYTE, imgData);
            glGenerateMipmap(GL_TEXTURE_2D);
            Log::info("Texture Generated From File: " + file);
        } else {
            THROW_ERROR(state, "Texture File Read Error. File Name: " + file);
        }
        stbi_image_free(imgData);
    }
    
    unsigned int getID() {return mTex;}

    void bind(int index) {
        glActiveTexture(GL_TEXTURE0+index);
        glBindTexture(GL_TEXTURE_2D, mTex);
    }

   private:
    unsigned int mTex;
    Rect mBorder;

    int imgWidth, imgHeight, nrChannels;
    unsigned char* imgData;
};


static unsigned int last_tex_id = 0;
static vector<Texture*> textures;

static Texture* create_texture(std::string file) {
    Texture* tex = new Texture(file, last_tex_id++);
    textures.push_back(tex);
    return tex;
}

};  // namespace Textures
#endif
