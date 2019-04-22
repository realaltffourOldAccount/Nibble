#ifndef OBJECT_H
#define OBJECT_H

#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
#include <glm/glm.hpp>

#include "univ_includes.h"
#include "buffer.h"

#include "texture.h"
#include "shaders.h"
#include "VBO.h"
#include "IBO.h"
#include "VAO.h"
#include "mvp.h"

#include "Rect.h"

// Objects are 2D textures, due to the project being simple,
// requiring only to draw 2D sprites

namespace Object {

  static std::map<std::string, Object*> objs;

  static void createObject(std::string name, std::string text_filename) {}

  class Object {
    public:
      Object(std::string filename, Rect shape) {
           
      }
      
    private:
      Texture* tex = nullptr;
      Rect _shape = nullptr;
      VBO* vbo = nullptr;
      IBO* ibo = nullptr;
      VAO* vao = nullptr;

      GLbyte *vertices = nullptr;
      GLbyte *indices = nullptr;

      vector<Shaders::ShaderAttribs*> shader_attribs;
  }

}

#endif
