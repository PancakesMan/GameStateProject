#include "Application2D.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"

#include "GameStateManager.h"
#include "SplashState.h"
#include "PauseState.h"
#include "GameState.h"
#include "MenuState.h"
#include "ControlsState.h"
#include "GameOverState.h"
#include "ScoreState.h"

Application2D::Application2D() {
	m_pause = 80;
	m_moveForward = 87;
	m_moveBackward = 83;
	m_rotateBodyLeft = 65;
	m_rotateBodyRight = 68;
	m_rotateBarrelLeft = 263;
	m_rotateBarrelRight = 262;
	m_shoot = 32;

	highScores = DynamicArray<int>(5);
	highScores.AddToEnd(0);
	highScores.AddToEnd(0);
	highScores.AddToEnd(0);
	highScores.AddToEnd(0);
	highScores.AddToEnd(0);

	srand((unsigned)time(NULL));
}

Application2D::~Application2D() {

}

float Application2D::getRuntime() {
	return m_timer;
}

bool Application2D::startup() {
	
	m_2dRenderer = new aie::Renderer2D();

	m_gameStateManager = std::unique_ptr<GameStateManager>(new GameStateManager());

	// Add states to the State Manager
	m_gameStateManager->setState((int)eStateID::SPLASH, new SplashState(this));
	m_gameStateManager->setState((int)eStateID::PAUSE, new PauseState(this));
	m_gameStateManager->setState((int)eStateID::GAME, new GameState(this));
	m_gameStateManager->setState((int)eStateID::MENU, new MenuState(this));
	m_gameStateManager->setState((int)eStateID::CONTROLS, new ControlsState(this));
	m_gameStateManager->setState((int)eStateID::GAME_OVER, new GameOverState(this));
	m_gameStateManager->setState((int)eStateID::SCORES, new ScoreState(this));

	m_gameStateManager->pushState((int)eStateID::SPLASH);

	m_cameraX = 0;
	m_cameraY = 0;
	m_timer = 0;

	return true;
}

void Application2D::shutdown() {
}

void Application2D::update(float deltaTime) {

	m_timer += deltaTime;

	// input example
	aie::Input* input = aie::Input::getInstance();

	m_gameStateManager->updateStates(deltaTime);
}

void Application2D::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// set the camera position before we begin rendering
	m_2dRenderer->setCameraPos(m_cameraX, m_cameraY);

	// begin drawing sprites
	m_2dRenderer->begin();

	m_gameStateManager->renderStates(m_2dRenderer);

	// done drawing sprites
	m_2dRenderer->end();
}