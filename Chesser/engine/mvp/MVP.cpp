#include "MVP.h"

GEngine::MVP::MVP(glm::mat4 model, glm::mat4 view, glm::mat4 proj) {
	this->_model = model;
	this->_view = view;
	this->_proj = proj;

	this->calc();
}

GEngine::MVP::~MVP(void) { this->destroy(); }

void GEngine::MVP::bind(GLuint program) {
	GLuint mvpID = glGetUniformLocation(program, "MVP");
	if (mvpID == -1) {
		THROW_ERROR("Could not locate 'MVP' uniform matrix.",
					Log::GenLogID(__LINE__, __FILE__, "Initiator", __func__));
	}

	calc();
	glUniformMatrix4fv(mvpID, 1, GL_FALSE, &_mvp[0][0]);
}

void GEngine::MVP::updateModel(const glm::mat4 model) {
	this->_model = model;
	calc();
}

void GEngine::MVP::updateView(const glm::mat4 view) {
	this->_view = view;
	calc();
}

void GEngine::MVP::updateProj(const glm::mat4 proj) {
	this->_proj = proj;
	calc();
}

glm::mat4 GEngine::MVP::getModel(void) const { return _model; }
glm::mat4 GEngine::MVP::getView(void) const { return _view; }
glm::mat4 GEngine::MVP::getProj(void) const { return _proj; }

glm::mat4 GEngine::MVP::getMVP(void) {
	calc();
	return _model;
}

void GEngine::MVP::destroy(void) {
	_model = glm::mat4(1.0f);
	_view = glm::mat4(1.0f);
	_proj = glm::mat4(1.0f);
	_mvp = glm::mat4(1.0f);
}

void GEngine::MVP::calc(void) {
	this->_mvp = this->_proj * this->_view * this->_model;
}