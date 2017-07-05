#pragma once
#include "IGameState.h"

class MenuState : public IGameState
{
public:
	MenuState(Application2D* _app);
	virtual ~MenuState();

	virtual void update(float deltaTime);
	virtual void render(aie::Renderer2D* renderer);

private:
	Button* m_start;
	Button* m_controls;
	Button* m_scores;
	Button* m_quit;
};