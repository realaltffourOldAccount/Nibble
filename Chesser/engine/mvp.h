#ifndef MVP_H
#define MVP_H

#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
#include <glm/glm.hpp>

#include "univ_includes.h"

namespace MVP {
struct mvp {
  glm::mat4 model;
  glm::mat4 view;
  glm::mat4 proj;
  glm::mat4 _mvp;
};

std::map<std::string, mvp*> mvps;

static void newMVP(std::string name, glm::mat4 model, glm::mat4 view, 
    glm::mat4 projection) {
    mvp new_mvp = makeMVP(model, view, projection);
    mvps[name] = new_mvp;
}

static mvp makeMVP(glm::mat4 model, glm::mat4 view, 
    glm::mat4 projection) {
    mvp res;
    res.model = model;
    res.view = view;
    res.proj = projection;
    res.mvp = projection * view * model; 
    return res;
}

// this assumes that program is already bound
static void bindMVP(std::string name, GLuint program) {
  auto _mvp = mvps[name];
  GLuint mvpID = glGetUniformLocation(program, "MVP");
  if (mvpID == -1) {//error
    THROW_ERROR("Could not find MVP matrix.");
  }
  glUniformMatrix4fv(mvpID, 1, GL_FALSE, &_mvp._mvp)
}

static void clean() {
    std::map<std::string, mvp*>::iterator it;
    for (it = mvps.begin(); it != mvps.end(); it++){
      delete it->second;
    }
}

static mvp* getMVP(std::string name) {
  return mvps[name];
}

static glm::mat4 getModel(std::string name) {
  return mvps[name].model;
}

static glm::mat4 getView(std::string name) {
  return mvps[name].view;
}

static glm::mat4 getProj(std::string name) {
  return mvps[name].proj;
}

static void setMVP(std::string name, mvp _mvp) {
  mvps[name] = _mvp;
}

static void setModel(std::string name, glm::mat4 model) {
  mvps[name].model = model;
}

static void getView(std::string name, glm::mat4 view) {
  mvps[name].view = view;
}

static void getProj(std::string name, glm::mat4 proj) {
   mvps[name].proj = proj;
}

}

#endif
