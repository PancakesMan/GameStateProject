#include "PauseState.h"
#include "GameState.h"
#include "MenuState.h"

PauseState::PauseState(Application2D* _app) : IGameState(_app)
{
	m_restart = new Button(app->getWindowWidth() / 2, app->getWindowHeight() / 2, "Restart", m_font.get());
	m_resume = new Button(m_restart->getX(), m_restart->getY() + 40, "Resume", m_font.get());
	m_quit = new Button(m_restart->getX(), m_restart->getY() - 40, "Quit", m_font.get());
}

PauseState::~PauseState()
{
}

void PauseState::update(float deltaTime)
{
	aie::Input* input = aie::Input::getInstance();

	if (input->wasKeyPressed(app->m_pause)) {
		app->getGameStateManager()->popState();
	}

	if (input->wasMouseButtonPressed(0)) {
		if (m_resume->Collision()) {
			app->getGameStateManager()->popState();
		}
		else if (m_restart->Collision()) {
			// Set the game state to a new game
			app->getGameStateManager()->setState((int)eStateID::GAME, new GameState(app));

			app->getGameStateManager()->popState(); // Pop the pause state
			app->getGameStateManager()->popState(); // Pop the old game state

			// Push the new game state
			app->getGameStateManager()->pushState((int)eStateID::GAME);
		}
		else if (m_quit->Collision()) {
			// Push a new 
			app->getGameStateManager()->setState((int)eStateID::MENU, new MenuState(app));

			app->getGameStateManager()->popState(); // Pop the pause state
			app->getGameStateManager()->popState(); // Pop the old game state

			// Push the new menu state
			app->getGameStateManager()->pushState((int)eStateID::MENU);
		}
	}
}

void PauseState::render(aie::Renderer2D* renderer)
{
	m_resume->Draw(renderer);
	m_restart->Draw(renderer);
	m_quit->Draw(renderer);
}
