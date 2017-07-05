#pragma once
#include "IGameState.h"

class PauseState : public IGameState
{
public:
	PauseState(Application2D* _app);
	virtual ~PauseState();

	virtual void update(float deltaTime);
	virtual void render(aie::Renderer2D* renderer);

private:
	Button* m_resume;
	Button* m_restart;
	Button* m_quit;
};