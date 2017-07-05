#pragma once
#include "IGameState.h"

class ControlsState : public IGameState
{
public:
	ControlsState(Application2D* _app);
	virtual ~ControlsState();

	virtual void update(float deltaTime);
	virtual void render(aie::Renderer2D* renderer);

private:
	Button* m_back;

	Button* m_moveForward;
	Button* m_moveBackward;
	Button* m_rotateLeft;
	Button* m_rotateRight;
	Button* m_rotateBarrelLeft;
	Button* m_rotateBarrelRight;
	Button* m_shoot;
	Button* m_pause;

	Map<int, std::string> validKeys;
};