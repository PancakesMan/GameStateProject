#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include "GameStateManager.h"
#include <memory>
#include <ctime>

class Application2D : public aie::Application {
public:

	Application2D();
	virtual ~Application2D();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

	float getRuntime();

	GameStateManager* getGameStateManager() { return m_gameStateManager.get(); }

	int m_moveForward, m_moveBackward, m_rotateBodyLeft, m_rotateBodyRight, m_rotateBarrelLeft, m_rotateBarrelRight, m_shoot, m_pause;
	DynamicArray<int> highScores;

protected:
	aie::Renderer2D*                    m_2dRenderer;
	std::unique_ptr<GameStateManager>   m_gameStateManager;

	float m_cameraX, m_cameraY;
	float m_timer;
};