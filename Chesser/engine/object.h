#ifndef OBJECT_H
#define OBJECT_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "buffer.h"
#include "univ_includes.h"

#include "ibo.h"
#include "mvp.h"
#include "shaders.h"
#include "textures.h"
#include "vao.h"
#include "vbo.h"

#include "Rect.h"

// Objects are 2D textures, due to the project being simple,
// requiring only to draw 2D sprites

namespace Object {

class Obj {
public:
  Obj(std::string name, std::string filename, Rect shape, Textures::Texture* tex = nullptr
      Point texcord_top_left = Point(0.0f,1.0f),
      Point texcord_top_right = Point(1.0f, 1.0f),
      Point texcord_bot_left = Point(0.0f, 0.0f),
      Point texcord_bot_right = Point(1.0f, 0.0f)) {

    // Set this instance.
    _shape = shape;

    // Check if texture is supplied.
    if (tex != nullptr)
      _tex = tex; // Dont reload the texture.
    else // Load the texture only when the texture isn't supplied.
      _tex = Textures::create_texture(filename); 

    indices = new GLuint[6]{
        0, 1, 3, // first triangle
        1, 2, 3, // second triangle
    };

    // Creat Indices buffer object
    IBOs::createIBO(name + "_IBO", GL_STATIC_DRAW, sizeof(GLuint) * 6,
                    indices);
    ibo = IBOs::ibo[name + "_IBO"];

    // Place holders for the buffer object.
    GLfloat tr_x = _shape.x + _shape.width;
    GLfloat tr_y = _shape.y + _shape.height;
    GLfloat tl_x = _shape.x;
    GLfloat tl_y = _shape.y + _shape.height;

    GLfloat br_x = _shape.x + _shape.width;
    GLfloat br_y = _shape.y;
    GLfloat bl_x = _shape.x;
    GLfloat bl_y = _shape.y;

    GLfloat ttr_x = texcord_top_right.x;
    GLfloat ttr_y = texcord_top_right.y;
    GLfloat ttl_x = texcord_top_left.x;
    GLfloat ttl_y = texcord_top_right.y;

    GLfloat tbr_x = texcord_bot_right.x;
    GLfloat tbr_y = texcord_bot_right.y;
    GLfloat tbl_x = texcord_bot_left.x;
    GLfloat tbl_y = texcord_bot_right.y;

    // Set the buffer data.
    buffer_data = new GLfloat[32]{
        // positions        // colors           // texture cords
        tr_x, tr_y, 0.0f,   1.0f, 1.0f, 1.0f,   ttr_x, ttr_y, // top right
        br_x, br_y, 0.0f,   1.0f, 1.0f, 1.0f,   tbr_x, tbr_y, // bottom right
        bl_x, bl_y, 0.0f,   1.0f, 1.0f, 1.0f,   tbl_x, tbl_y, // bottom left
        tl_x, tl_y, 0.0f,   1.0f, 1.0f, 1.0f,   ttl_x, ttl_y, // top left
    };

    // Create the buffer and initialize it.
    VBOs::createVBO(name + "_VBO", GL_STATIC_DRAW, sizeof(GLfloat) * 32,
                    buffer_data);
    vbo = VBOs::vbo[name + "_VBO"];

    // Set up the vertex attributes: pos, color, tcords, etc.
    VAOs::ShaderAttrib *position_attrib;
    VAOs::ShaderAttrib *color_attrib;
    VAOs::ShaderAttrib *tex_cord_attrib;

    position_attrib = new VAOs::ShaderAttrib();
    position_attrib->index = SHADER_ATTRIB_POS;
    position_attrib->size = 3;
    position_attrib->stride = 8 * sizeof(GLfloat);
    position_attrib->offset = (void *)0;
    position_attrib->type = GL_FLOAT;
    position_attrib->isNorm = false;
    position_attrib->isEnable = true;

    color_attrib = new VAOs::ShaderAttrib();
    color_attrib->index = SHADER_ATTRIB_COLOR;
    color_attrib->size = 3;
    color_attrib->stride = 8 * sizeof(GLfloat);
    color_attrib->offset = (void *)(3 * sizeof(GLfloat));
    color_attrib->type = GL_FLOAT;
    color_attrib->isNorm = false;
    color_attrib->isEnable = true;

    tex_cord_attrib = new VAOs::ShaderAttrib();
    tex_cord_attrib->index = SHADER_ATTRIB_TEXCOORD;
    tex_cord_attrib->size = 2;
    tex_cord_attrib->stride = 8 * sizeof(GLfloat);
    tex_cord_attrib->offset = (void *)(6 * sizeof(GLfloat));
    tex_cord_attrib->type = GL_FLOAT;
    tex_cord_attrib->isNorm = false;
    tex_cord_attrib->isEnable = true;

    shader_attribs.push_back(position_attrib);
    shader_attribs.push_back(color_attrib);
    shader_attribs.push_back(tex_cord_attrib);

    // Create the vertex specifications of the buffer object.
    VAOs::createVAO(name + "_VAO", vbo, shader_attribs);
    vao = VAOs::vao[name + "_VAO"];
  }

  void bind(int tex_index) {
    _tex->bind(tex_index);
    vao->bind();
    vbo->bind();
    ibo->bind();
  }

  glm::mat4 getModel() { return model; }

  void translate(glm::vec2 vec) {
    glm::mat4 trans =
        glm::translate(glm::mat4(1.0f), glm::vec3(vec.x, vec.y, 1.0f));
    glm::mat4 new_model = model * trans;
    model = new_model;
  }

  void scale(glm::vec2 vec) {
    model *glm::scale(glm::mat4(1.0f), glm::vec3(vec.x, vec.y, 1.0f));
  }

  auto getTex() {return _tex;}

private:
  Textures::Texture *_tex = nullptr;
  BufferObject *vbo = nullptr;
  BufferObject *ibo = nullptr;
  VAOs::VAO *vao = nullptr;
  Rect _shape;

  GLfloat *buffer_data;
  GLuint *indices = nullptr;

  vector<VAOs::ShaderAttrib *> shader_attribs;

  glm::mat4 model = glm::mat4(1.0f);
};

static std::map<std::string, Obj *> objs;

static void createObject(std::string name, std::string text_filename,
                         Rect shape) {
  Obj *new_obj = new Obj(name, text_filename, shape);
  objs.insert(std::pair<std::string, Obj*>(name, new_obj));
}
} // namespace Object

#endif
