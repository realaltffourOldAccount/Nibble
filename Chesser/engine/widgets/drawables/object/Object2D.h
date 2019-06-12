/**
 * @file Object.h
 * @author Ayham Mamoun (ayhamaboualfadl@gmail.com)
 * @brief Contains an abstract definition of an Object.
 * @version 0.1
 * @date 2019-06-08
 *
 */

#ifndef OBJECT2D_H
#define OBJECT2D_H
#pragma once

#include "common.h"

#include <engine/Point.h>
#include <engine/Rect.h>

#include <engine/buffers/buffers.h>
#include <engine/mvp/MVP.h>
#include <engine/shaders/Shaders.h>
#include <engine/textures/Texture.h>

#include <engine/widgets/drawables/Drawable.h>

namespace GEngine {
namespace Widgets {
namespace Drawables {

extern GEngine::Shader* do_shaders;

class Object2D : public Drawable {
   public:
	Object2D(Rect shape, GEngine::MVP* mvp);
	Object2D(Rect shape, GEngine::MVP* mvp, std::string tex_file);
	Object2D(Rect shape, GEngine::MVP* mvp, GEngine::Texture* tex = nullptr,
			 Rect texcord = Rect(0, 0, 1, 1));

	~Object2D(void);

	virtual void init();

	void render(void) override;
	void tick(void) override;
	void destroy(void) override;

	bool eventHandler(Event* evt) override;

   private:
	void initShaders(void);
	void initDefaultObject(void);

   protected:
	Rect mShape;
	std::string mTexFile = "";
	Rect mTexCord;
	GEngine::MVP* mMVP = nullptr;

	GEngine::Texture* mTex = nullptr;
	GEngine::VBO* mVBO = nullptr;
	GEngine::IBO* mIBO = nullptr;
	GEngine::VAO* mVAO = nullptr;

	GLfloat* mBufferData = nullptr;
	GLuint* mIndicesData = nullptr;

	vector<GEngine::ShaderAttrib*> mShaderAttribs;
};
}  // namespace Drawables
}  // namespace Widgets
}  // namespace GEngine

#endif