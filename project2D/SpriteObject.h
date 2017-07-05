#pragma once
#include "Texture.h"
#include "SceneObject.h"

class SpriteObject : public SceneObject
{
public:
	SpriteObject(aie::Texture* texture) : m_texture(texture) {}
	virtual ~SpriteObject() {}

	virtual void draw(aie::Renderer2D* renderer)
	{
		if (!destroyed)
		{
			renderer->drawSpriteTransformed3x3(m_texture, (float*)&m_globalTransform);
			SceneObject::draw(renderer);
		}
	}

	int getWidth()
	{
		return m_texture->getWidth();
	}

	int getHeight()
	{
		return m_texture->getHeight();
	}

protected:
	aie::Texture* m_texture;
};