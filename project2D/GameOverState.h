#pragma once
#include "IGameState.h"

class GameOverState : public IGameState
{
public:
	GameOverState(Application2D* _app);
	virtual ~GameOverState();

	virtual void update(float deltaTime);
	virtual void render(aie::Renderer2D* renderer);

	static int score;
	static std::string message;
private:
	//
};
