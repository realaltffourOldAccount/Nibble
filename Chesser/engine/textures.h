#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include "univ_includes.h"

#include "Rect.h"

namespace Textures {

class Texture {
   public:
    Texture(std::string file, int tex_id = 0);
    
    unsigned int getID() {return mTex;}

    void bind(int index) {
        glActiveTexture(GL_TEXTURE0+index);
        glBindTexture(GL_TEXTURE_2D, mTex);
    }
    int x,y,n;
   private:
    unsigned int mTex;
    Rect mBorder;
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
