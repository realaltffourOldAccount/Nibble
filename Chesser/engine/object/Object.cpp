#include "Object.h"

GEngine::Object::Object(std::string tex_file, Rect shape, Rect texcord,
						GEngine::Texture* tex) {
	_shape = shape;

	// Check if texture is supplied
	if (tex != nullptr)
		_tex = tex;  // Dont reload texture
	else			 // Load texture only when the texture isn't supplied.
		_tex = new GEngine::Texture(tex_file);

	_indices_data = new GLuint[6]{
		0, 1, 3,  // first triangle
		1, 2, 3,  // second triangle
	};

	// Create indices buffer
	this->_ibo =
		new GEngine::IBO(GL_STATIC_DRAW, sizeof(GLuint) * 6, _indices_data);

	// Place holders for the buffer object.
	GLfloat tr_x = _shape.x + _shape.w;
	GLfloat tr_y = _shape.y + _shape.h;
	GLfloat tl_x = _shape.x;
	GLfloat tl_y = _shape.y + _shape.h;

	GLfloat br_x = _shape.x + _shape.w;
	GLfloat br_y = _shape.y;
	GLfloat bl_x = _shape.x;
	GLfloat bl_y = _shape.y;

	GLfloat ttr_x = texcord.x + texcord.w;
	GLfloat ttr_y = texcord.y + texcord.h;
	GLfloat ttl_x = texcord.x;
	GLfloat ttl_y = texcord.y + texcord.h;

	GLfloat tbr_x = texcord.x + texcord.w;
	GLfloat tbr_y = texcord.y;
	GLfloat tbl_x = texcord.x;
	GLfloat tbl_y = texcord.y;

	// Set the buffer data.
	_buffer_data = new GLfloat[32]{
		// positions        // colors           // texture cords
		tr_x, tr_y, 0.0f, 1.0f, 1.0f, 1.0f, ttr_x, ttr_y,  // top right
		br_x, br_y, 0.0f, 1.0f, 1.0f, 1.0f, tbr_x, tbr_y,  // bottom right
		bl_x, bl_y, 0.0f, 1.0f, 1.0f, 1.0f, tbl_x, tbl_y,  // bottom left
		tl_x, tl_y, 0.0f, 1.0f, 1.0f, 1.0f, ttl_x, ttl_y,  // top left
	};

	//// Set the buffer data.
	//_buffer_data = new GLfloat[32]{
	//    // positions          // colors           // texture coords
	//    0.5f,  0.5f,  0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top right
	//    0.5f,  -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom right
	//    -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
	//    -0.5f, 0.5f,  0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f  // top left
	//};

	this->_vbo =
		new GEngine::VBO(GL_STATIC_DRAW, sizeof(GLfloat) * 32, _buffer_data);

	// Set up the vertex attributes: pos, color, tcords, etc.
	GEngine::ShaderAttrib* position_attrib;
	GEngine::ShaderAttrib* color_attrib;
	GEngine::ShaderAttrib* tex_cord_attrib;

	position_attrib = new GEngine::ShaderAttrib();
	position_attrib->_index = SHADER_ATTRIB_POS;
	position_attrib->_size = 3;
	position_attrib->_stride = 8 * sizeof(GLfloat);
	position_attrib->_offset = (void*)0;
	position_attrib->_type = GL_FLOAT;
	position_attrib->_isNorm = false;
	position_attrib->_isEnable = true;

	color_attrib = new GEngine::ShaderAttrib();
	color_attrib->_index = SHADER_ATTRIB_COLOR;
	color_attrib->_size = 3;
	color_attrib->_stride = 8 * sizeof(GLfloat);
	color_attrib->_offset = (void*)(3 * sizeof(GLfloat));
	color_attrib->_type = GL_FLOAT;
	color_attrib->_isNorm = false;
	color_attrib->_isEnable = true;

	tex_cord_attrib = new GEngine::ShaderAttrib();
	tex_cord_attrib->_index = SHADER_ATTRIB_TEXCOORD;
	tex_cord_attrib->_size = 2;
	tex_cord_attrib->_stride = 8 * sizeof(GLfloat);
	tex_cord_attrib->_offset = (void*)(6 * sizeof(GLfloat));
	tex_cord_attrib->_type = GL_FLOAT;
	tex_cord_attrib->_isNorm = false;
	tex_cord_attrib->_isEnable = true;

	this->_shader_attribs.push_back(position_attrib);
	this->_shader_attribs.push_back(color_attrib);
	this->_shader_attribs.push_back(tex_cord_attrib);

	this->_vao = new GEngine::VAO(this->_vbo, _shader_attribs);
}

GEngine::Object::~Object(void) { this->destroy(); }

void GEngine::Object::render(GEngine::Shader* shader, GEngine::MVP* mvp) {
	shader->bind();
	mvp->updateModel(this->getModel());
	mvp->bind(shader->getProgId());
	this->bind();
	GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0));
	this->unbind();
	shader->unbind();
}

void GEngine::Object::bind(void) const {
	this->_tex->bind();
	this->_vao->bind();
	this->_vbo->bind();
	this->_ibo->bind();
}
void GEngine::Object::unbind(void) const {
	this->_tex->unbind();
	this->_vao->unbind();
	this->_vbo->unbind();
	this->_ibo->unbind();
}

glm::mat4 GEngine::Object::getModel(void) const { return this->model; }

void GEngine::Object::translate(glm::vec2 vec) {
	this->model = glm::translate(this->model, glm::vec3(vec.x, vec.y, 0.0f));
}

void GEngine::Object::scale(glm::vec2 vec) {
	this->model = glm::scale(this->model, glm::vec3(vec.x, vec.y, 1.0f));
}

GEngine::Texture* GEngine::Object::getTex(void) const { return this->_tex; }

void GEngine::Object::destroy(void) {
	this->_tex->destroy();
	this->_vbo->destroy();
	this->_ibo->destroy();
	this->_vao->destroy();
}