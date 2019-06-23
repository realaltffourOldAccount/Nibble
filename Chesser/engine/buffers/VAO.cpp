#include "VAO.h"

GEngine::VAO::VAO(GEngine::VBO* vbo, vector<ShaderAttrib*> attribs) {
	_attribs = attribs;
	// if (g_opengl_ver_major >= 3) {
	this->_vbo = vbo;
	GLCall(glGenVertexArrays(1, &this->_vaoID));
	GLCall(glBindVertexArray(this->_vaoID));
	this->_vbo->bind();
	for (int i = 0; i < attribs.size(); i++) this->enableAttrib(attribs[i]);
	GLCall(glBindVertexArray(0));
	//#endif
	//} else {
	//}
}

GEngine::VAO::VAO(vector<ShaderAttrib*> attribs) {
	_attribs = attribs;
	// if (g_opengl_ver_minor >= 3) {
	//#ifndef __ANDROID__
	GLCall(glGenVertexArrays(1, &this->_vaoID));
	GLCall(glBindVertexArray(this->_vaoID));
	for (int i = 0; i < attribs.size(); i++) this->enableAttrib(attribs[i]);
	GLCall(glBindVertexArray(0));
	//#endif
	//}
}

GEngine::VAO::~VAO(void) { this->destroy(); }

void GEngine::VAO::bind(void) {
	// if (g_opengl_ver_major >= 3) {
	GLCall(glBindVertexArray(this->_vaoID));
	//} else {
	//	for (int i = 0; i < this->_attribs.size(); i++)
	//		this->enableAttrib(this->_attribs[i]);
	//}
}

void GEngine::VAO::unbind(void) {
	/*  if (g_opengl_ver_major >= 3)
	 */
	GLCall(glBindVertexArray(0));
}

void GEngine::VAO::destroy(void) {
	// if (g_opengl_ver_major >= 3) {
	//#ifndef __ANDROID__
	delete this->_vbo;
	// this->_vbo->destroy();
	GLCall(glDeleteVertexArrays(1, &this->_vaoID));
	//#endif
	//}
}

void GEngine::VAO::enableAttrib(ShaderAttrib* attrib) {
	GLCall(glEnableVertexAttribArray(attrib->_index));
	GLCall(glVertexAttribPointer(attrib->_index, attrib->_size, attrib->_type,
								 attrib->_isNorm, attrib->_stride,
								 attrib->_offset));
}