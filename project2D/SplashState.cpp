#include "SplashState.h"

SplashState::SplashState(Application2D* _app) : IGameState(_app)
{
	m_splash = resources.getTexture("./textures/splash.png");
	glass = new Hourglass(45, 55);
}

SplashState::~SplashState()
{
}

void SplashState::update(float deltaTime)
{
	m_runtime += deltaTime;
	if (m_runtime > 3.0f) {
		app->getGameStateManager()->popState();
		app->getGameStateManager()->pushState((int)eStateID::MENU);
	}
	glass->update(deltaTime);
}

void SplashState::render(aie::Renderer2D* renderer)
{
	renderer->setRenderColour(1, 1, 1, 1);
	renderer->drawSprite(m_splash.get(), app->getWindowWidth() / 2, app->getWindowHeight() / 2);
	glass->Draw(renderer);
}
