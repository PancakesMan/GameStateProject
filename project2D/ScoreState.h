#pragma once
#include "IGameState.h"

class ScoreState : public IGameState
{
public:
	ScoreState(Application2D* _app);
	virtual ~ScoreState();

	virtual void update(float deltaTime);
	virtual void render(aie::Renderer2D* renderer);

private:
	Button* m_back;
};