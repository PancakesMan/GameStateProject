#include "GameOverState.h"
#include <algorithm>

int GameOverState::score = 0;

GameOverState::GameOverState(Application2D* _app) : IGameState(_app) {
	//
}

GameOverState::~GameOverState() {}

void GameOverState::update(float deltaTime) {
	m_runtime += deltaTime;
	if (m_runtime > 3.0f && aie::Input::getInstance()->getPressedKeys().size() > 0) {
		app->highScores[4] = score;
		std::sort(std::begin(app->highScores), std::end(app->highScores), [](int a, int b) {return a > b; });

		app->getGameStateManager()->popState();
		app->getGameStateManager()->pushState((int)eStateID::MENU);
	}
}

void GameOverState::render(aie::Renderer2D* renderer) {
	std::shared_ptr<aie::Font> f1 = resources.getFont("./font/consolas.ttf", 50);
	float t0w = f1.get()->getStringWidth("GAME OVER");
	float t0h = f1.get()->getStringHeight("GAME OVER");

	renderer->drawText(f1.get(), "GAME OVER", app->getWindowWidth() / 2 - (t0w / 2), app->getWindowHeight() / 3 * 2);

	std::string scoreMsg = "You got a score of: " + std::to_string(score);
	float t1w = m_font.get()->getStringWidth(scoreMsg.c_str());
	float t1h = m_font.get()->getStringHeight(scoreMsg.c_str());

	renderer->drawText(m_font.get(), scoreMsg.c_str(), app->getWindowWidth() / 2 - (t1w / 2), app->getWindowHeight() / 2);

	float t2w = m_font->getStringWidth("Press any key to continue...");
	float t2h = m_font->getStringHeight("Press any key to continue...");

	if (m_runtime > 3.0f)
		renderer->drawText(m_font.get(), "Press any key to continue...", app->getWindowWidth() / 2 - (t2w / 2), app->getWindowHeight() / 3);
}