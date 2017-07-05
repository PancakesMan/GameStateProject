#include "MenuState.h"
#include "GameState.h"

MenuState::MenuState(Application2D* _app) : IGameState(_app) {
	m_font = resources.getFont("./font/consolas.ttf", 28);

	m_start = new Button(app->getWindowWidth() / 2, app->getWindowHeight() / 2 - 60, "Start Game", m_font.get());
	m_controls = new Button(app->getWindowWidth() / 2, m_start->getY() - 40, "Controls", m_font.get());
	m_scores = new Button(app->getWindowWidth() / 2, m_controls->getY() - 40, "Scores", m_font.get());
	m_quit = new Button(app->getWindowWidth() / 2, m_scores->getY() - 40, "Exit", m_font.get());
}
MenuState::~MenuState() {}

void MenuState::update(float deltaTime) {
	aie::Input* input = aie::Input::getInstance();

	if (input->wasMouseButtonPressed(0)) {
		if (m_start->Collision()) {
			app->getGameStateManager()->popState();

			app->getGameStateManager()->setState((int)eStateID::GAME, new GameState(app));
			app->getGameStateManager()->pushState((int)eStateID::GAME);
		}
		else if (m_controls->Collision()) {
			app->getGameStateManager()->popState();
			app->getGameStateManager()->pushState((int)eStateID::CONTROLS);
		}
		else if (m_scores->Collision()) {
			app->getGameStateManager()->popState();
			app->getGameStateManager()->pushState((int)eStateID::SCORES);
		}
		else if (m_quit->Collision()) {
			app->quit();
		}
	}
}

void MenuState::render(aie::Renderer2D* renderer) {
	renderer->drawSprite(resources.getTexture("./textures/splash.png").get(), app->getWindowWidth() / 2, app->getWindowHeight() / 2 + 150, 1000, 400, 0, 0);

	m_start->Draw(renderer);
	m_controls->Draw(renderer);
	m_scores->Draw(renderer);
	m_quit->Draw(renderer);
}