#include "ScoreState.h"
#include "MenuState.h"

ScoreState::ScoreState(Application2D* _app) : IGameState(_app) {
	m_font = resources.getFont("./font/consolas.ttf", 22);
	m_back = new Button(app->getWindowWidth() / 2, 150, "Back", m_font.get());
}
ScoreState::~ScoreState() {}

void ScoreState::update(float deltaTime) {
	aie::Input* input = aie::Input::getInstance();
	if (input->wasMouseButtonPressed(0)) {
		if (m_back->Collision()) {
			app->getGameStateManager()->popState();
			app->getGameStateManager()->pushState((int)eStateID::MENU);
		}
	}
}

void ScoreState::render(aie::Renderer2D* renderer) {
	m_back->Draw(renderer);

	renderer->setRenderColour(1, 1, 1, 1);
	std::string s1 = "1. " + std::to_string(app->highScores[0]);
	std::string s2 = "2. " + std::to_string(app->highScores[1]);
	std::string s3 = "3. " + std::to_string(app->highScores[2]);
	std::string s4 = "4. " + std::to_string(app->highScores[3]);
	std::string s5 = "5. " + std::to_string(app->highScores[4]);

	float t0 = resources.getFont("./font/consolas.ttf", 30)->getStringWidth("HIGH SCORES");

	float t1 = m_font.get()->getStringWidth(s1.c_str());
	float t11 = m_font.get()->getStringHeight(s1.c_str());

	float t2 = m_font.get()->getStringWidth(s2.c_str());
	float t21 = m_font.get()->getStringHeight(s2.c_str());

	float t3 = m_font.get()->getStringWidth(s3.c_str());
	float t31 = m_font.get()->getStringHeight(s3.c_str());

	float t4 = m_font.get()->getStringWidth(s4.c_str());
	float t41 = m_font.get()->getStringHeight(s4.c_str());

	float t5 = m_font.get()->getStringWidth(s5.c_str());
	float t51 = m_font.get()->getStringHeight(s5.c_str());

	renderer->drawText(resources.getFont("./font/consolas.ttf", 30).get(), "HIGH SCORES", app->getWindowWidth() / 2 - t0 / 2, app->getWindowHeight() / 4 * 3);
	renderer->drawText(m_font.get(), s1.c_str(), app->getWindowWidth() / 2 - t1 / 2, (app->getWindowHeight() / 3 * 2) - (t11 / 2));
	renderer->drawText(m_font.get(), s2.c_str(), app->getWindowWidth() / 2 - t2 / 2, (app->getWindowHeight() / 3 * 2) - 35 - (t21 / 2));
	renderer->drawText(m_font.get(), s3.c_str(), app->getWindowWidth() / 2 - t3 / 2, (app->getWindowHeight() / 3 * 2) - 70 - (t31 / 2));
	renderer->drawText(m_font.get(), s4.c_str(), app->getWindowWidth() / 2 - t4 / 2, (app->getWindowHeight() / 3 * 2) - 105 - (t41 / 2));
	renderer->drawText(m_font.get(), s5.c_str(), app->getWindowWidth() / 2 - t5 / 2, (app->getWindowHeight() / 3 * 2) - 140 - (t51 / 2));
}