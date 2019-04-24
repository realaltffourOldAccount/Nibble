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
    Object(std::string name, std::string filename, Rect shape) {
        _shape = shape;
        tex = create_texture(filename, _shape);

        indices = new GLbyte[6] {
            0, 1, 3,  // first triangle
            1, 2, 3,  // second triangle
        };

        createIBO(name+"_IBO", GL_STATIC_DRAW, sizeof(GLbyte)*6,
                  indices);
        ibo = IBOs::ibo[name+"_IBO"];

        int tr_x = _shape.x + _shape.width;
        int tr_y = _shape.y + _shape.height;
        int tl_x = _shape.x;
        int tl_y = _shape.y + _shape.height;

        int br_x = _shape.x + _shape.width;
        int br_y = _shape.y;
        int bl_x = _shape.x;
        int bl_y = _shape.y + _shape.height;

        buffer_data = new GLbyte[32] = {
            // positions        // colors           // texture cords
            tr_x, tr_y, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
            br_x, br_y, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
            bl_x, bl_y, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
            tl_x, tl_y, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f, // top left
        };

        createVBO(name+"_VBO", GL_STATIC_DRAW, sizeof(GLbyte)*32, buffer_data);
        vbo = VBOs::vbo[name+"_VBO"];

        VAOs::ShaderAttrib* position_attrib, color_attrib, tex_cord_attrib;

        position_attrib = new VAOs::ShaderAttrib();
        position_attrib->index = SHADER_ATTRIB_POS;
        position_attrib->size = 3;
        position_attrib->stride = 8 * sizeof(GLbyte);
        position_attrib->offset = (void*)0;
        position_attrib->type = GL_BYTE;
        position_attrib->isNorm = false;
        position_attrib->isEnable = true;

        color_attrib = new VAOs::ShaderAttrib();
        color_attrib->index = SHADER_ATTRIB_COLOR;
        color_attrib->offset = (void*)(3*sizeof(GLbyte));
        color_attrib->type = GL_BYTE;
        color_attrib->isNorm = false;
        color_attrib->isEnable = true;

        tex_cord_attrib = new VAOs::ShaderAttrib();
        tex_cord_attrib->index = SHADER_ATTRIB_TEXCOORD;
        tex_cord_attrib->size = 2;
        tex_cord_attrib->stride = 8 * sizeof(GLbyte);
        tex_cord_attrib->offset = (void*)(6*sizeof(GLbyte));
        tex_cord_attrib->type = GL_BYTE;
        tex_cord_attrib->isNorm = false;
        tex_cord_attrib->isEnable = true;

        shader_attribs.push_back(position_attrib);
        shader_attribs.push_back(color_attrib);
        shader_attribs.push_back(tex_cord_attrib);
    }

    glm::mat4 getModel() {return model;}
    
    void translate(glm::vec2 vec) {
      glm::mat4 trans = glm::translate(glm::mat4(1.0f), glm::vec3(vec.x, vec.y, 1.0f));
      glm::mat4 new_model = model * trans;
      model = new_model;
    } 
    
private:
    Texture* tex = nullptr;
    Rect _shape = nullptr;
    VBO* vbo = nullptr;
    IBO* ibo = nullptr;
    VAO* vao = nullptr;

    GLbyte *buffer_data = nullptr;
    GLbyte *indices = nullptr;

    vector<VAOs::ShaderAttribs*> shader_attribs;

    glm:mat4 model;
}

}

#endif
