#include "IGameState.h"

IGameState::IGameState(Application2D* _app) : app(_app)
{
	m_font = resources.getFont("./font/consolas.ttf", 22);
	m_runtime = 0;
}

IGameState::~IGameState()
{
}
