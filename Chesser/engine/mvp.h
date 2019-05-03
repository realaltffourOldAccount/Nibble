#ifndef MVP_H
#define MVP_H

#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
#include <glm/glm.hpp>

#include "univ_includes.h"

struct MVPInfo {
  glm::mat4 model;
  glm::mat4 view;
  glm::mat4 proj;
  glm::mat4 mvp;
};

class MVP {
public:
MVP() {}

std::map<std::string, MVPInfo*> mvps;
MVPInfo* makeMVP(glm::mat4 model, glm::mat4 view, 
    glm::mat4 projection) {
    MVPInfo* res = new MVPInfo();
    res->model = model;
    res->view = view;
    res->proj = projection;
    res->mvp = projection * view * model; 
    return res;
}


void newMVP(std::string name, glm::mat4 model, glm::mat4 view, 
    glm::mat4 projection) {
    MVPInfo* new_mvp = makeMVP(model, view, projection);
    mvps[name] = new_mvp;
}

void calcMVP(std::string name) {
  MVPInfo* calcd_mvp = mvps[name];
  calcd_mvp->mvp = calcd_mvp->proj * calcd_mvp->view * calcd_mvp->model;
}

// this assumes that program is already bound
void bindMVP(std::string name, GLuint program) {
  MVPInfo* _mvp = mvps[name];
  GLuint mvpID = glGetUniformLocation(program, "MVP");
  if (mvpID == -1) {//error
    THROW_ERROR(state, "Could not find MVP matrix.");
  }
  glm::mat4 mvp = _mvp->mvp;
  glUniformMatrix4fv(mvpID, 1, GL_FALSE, &mvp[0][0]);
}

void clean() {
    std::map<std::string, MVPInfo*>::iterator it;
    for (it = mvps.begin(); it != mvps.end(); it++){
      delete it->second;
    }
}

MVPInfo* getMVP(std::string name) {
  return mvps[name];
}

glm::mat4 getModel(std::string name) {
  return mvps[name]->model;
}

glm::mat4 getView(std::string name) {
  return mvps[name]->view;
}

glm::mat4 getProj(std::string name) {
  return mvps[name]->proj;
}

void setMVP(std::string name, MVPInfo *_mvp) {
  mvps[name] = _mvp;
}

void setModel(std::string name, glm::mat4 model) {
  mvps[name]->model = model;
}

void setView(std::string name, glm::mat4 view) {
  mvps[name]->view = view;
}

void setProj(std::string name, glm::mat4 proj) {
   mvps[name]->proj = proj;
}

};

#endif
