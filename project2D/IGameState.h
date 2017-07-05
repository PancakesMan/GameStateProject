#pragma once
#include <Renderer2D.h>
#include "ResourceManager.h"
#include "Application2D.h"
#include <Input.h>
#include <Font.h>
#include "Button.h"

class IGameState
{
public:
	IGameState(Application2D* _app);
	virtual ~IGameState();

	virtual void update(float deltaTime) = 0;
	virtual void render(aie::Renderer2D* renderer) = 0;

	Application2D* getApp() { return app; }

protected:
	Application2D* app;
	std::shared_ptr<aie::Font> m_font;

	float m_runtime;
};

