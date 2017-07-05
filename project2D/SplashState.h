#pragma once
#include "IGameState.h"
#include "Hourglass.h"

class SplashState : public IGameState
{
public:
	SplashState(Application2D* _app);
	virtual ~SplashState();

	virtual void update(float deltaTime);
	virtual void render(aie::Renderer2D* renderer);

private:
	std::shared_ptr<aie::Texture> m_splash;
	Hourglass* glass;
};

