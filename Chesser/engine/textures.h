#ifndef TEXTURE_H
#define TEXTURE_H

#include "chsr_api.h"
#include "vendor/stb_image.h"

#include "Rect.h"

namespace Textures {

static unsigned int last_tex_id = 0;

static void init_texs() {}

class Texture {
   public:
    Texture(std::string file, Rect border, int tex_id = 0) {
        glGenTextures(1, &mTex);
        glBindTexture(GL_TEXTURE_2D, mTex);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        imgData =
            stbi_load(file.c_str(), &imgWidth, &imgHeight, &nrChannels, 0);
        if (imgData) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, border.width, border.height,
                         0, GL_RGB, GL_UNSIGNED_BYTE, imgData);
            glGenerateMipmap(GL_TEXTURE_2D);
            Log::trace("Texture Generated From File: " + file);
        } else {
            THROW_ERROR(state, "Texture File Read Error. File Name: " + file);
        }
        stbi_image_free(imgData);
    }

   private:
    unsigned int mTex;
    Rect mBorder;

    int imgWidth, imgHeight, nrChannels;
    unsigned char* imgData;
};
};  // namespace Textures
#endif