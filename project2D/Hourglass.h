#pragma once
#include <Renderer2D.h>
#include "ResourceManager.h"

class Hourglass {
public:
	Hourglass(float _x, float _y) : x(_x), y(_y), timer(0) {
		m_texture = resources.getTexture("./textures/hourglass.png");
	}
	~Hourglass() {}

	void Draw(aie::Renderer2D* renderer) {
		renderer->setUVRect(((int)(timer * 7.f) % 7) / 7.f, 0, 1.f / 7, 1.f);
		renderer->drawSprite(m_texture.get(), x, y, 49, 85);
		renderer->setUVRect(0, 0, 1, 1);
	}

	void update(float deltaTime) {
		timer += deltaTime;
	 }

private:
	std::shared_ptr<aie::Texture> m_texture;
	float x, y;

	float timer;
};