#include "ControlsState.h"
#include "MenuState.h"

ControlsState::ControlsState(Application2D* _app) : IGameState(_app) {
	m_font = resources.getFont("./font/consolas.ttf", 22);
	m_back = new Button(app->getWindowWidth() / 2, 150, "Back", m_font.get());

	m_moveForward = new Button(app->getWindowWidth() / 3 * 2, app->getWindowHeight() / 3 * 2, "W", m_font.get());
	m_moveBackward = new Button(app->getWindowWidth() / 3 * 2, (app->getWindowHeight() / 3 * 2) - 35, "S", m_font.get());
	m_rotateLeft = new Button(app->getWindowWidth() / 3 * 2, (app->getWindowHeight() / 3 * 2) - 70, "A", m_font.get());
	m_rotateRight = new Button(app->getWindowWidth() / 3 * 2, (app->getWindowHeight() / 3 * 2) - 105, "D", m_font.get());
	m_rotateBarrelLeft = new Button(app->getWindowWidth() / 3 * 2, (app->getWindowHeight() / 3 * 2) - 140, "Left Arrow", m_font.get());
	m_rotateBarrelRight = new Button(app->getWindowWidth() / 3 * 2, (app->getWindowHeight() / 3 * 2) - 175, "Right Arrow", m_font.get());
	m_shoot = new Button(app->getWindowWidth() / 3 * 2, (app->getWindowHeight() / 3 * 2) - 210, "Space", m_font.get());
	m_pause = new Button(app->getWindowWidth() / 3 * 2, (app->getWindowHeight() / 3 * 2) - 245, "P", m_font.get());
	
	#pragma region Initialize Valid Keys Map
	validKeys[aie::EInputCodes::INPUT_KEY_A] = "A";
	validKeys[aie::EInputCodes::INPUT_KEY_B] = "B";
	validKeys[aie::EInputCodes::INPUT_KEY_C] = "C";
	validKeys[aie::EInputCodes::INPUT_KEY_D] = "D";
	validKeys[aie::EInputCodes::INPUT_KEY_E] = "E";
	validKeys[aie::EInputCodes::INPUT_KEY_F] = "F";
	validKeys[aie::EInputCodes::INPUT_KEY_G] = "G";
	validKeys[aie::EInputCodes::INPUT_KEY_H] = "H";
	validKeys[aie::EInputCodes::INPUT_KEY_I] = "I";
	validKeys[aie::EInputCodes::INPUT_KEY_J] = "J";
	validKeys[aie::EInputCodes::INPUT_KEY_K] = "K";
	validKeys[aie::EInputCodes::INPUT_KEY_L] = "L";
	validKeys[aie::EInputCodes::INPUT_KEY_M] = "M";
	validKeys[aie::EInputCodes::INPUT_KEY_N] = "N";
	validKeys[aie::EInputCodes::INPUT_KEY_O] = "O";
	validKeys[aie::EInputCodes::INPUT_KEY_P] = "P";
	validKeys[aie::EInputCodes::INPUT_KEY_Q] = "Q";
	validKeys[aie::EInputCodes::INPUT_KEY_R] = "R";
	validKeys[aie::EInputCodes::INPUT_KEY_S] = "S";
	validKeys[aie::EInputCodes::INPUT_KEY_T] = "T";
	validKeys[aie::EInputCodes::INPUT_KEY_U] = "U";
	validKeys[aie::EInputCodes::INPUT_KEY_V] = "V";
	validKeys[aie::EInputCodes::INPUT_KEY_W] = "W";
	validKeys[aie::EInputCodes::INPUT_KEY_X] = "X";
	validKeys[aie::EInputCodes::INPUT_KEY_Y] = "Y";
	validKeys[aie::EInputCodes::INPUT_KEY_Z] = "Z";
	validKeys[aie::EInputCodes::INPUT_KEY_SPACE] = "Space";
	validKeys[aie::EInputCodes::INPUT_KEY_LEFT] = "Left Arrow";
	validKeys[aie::EInputCodes::INPUT_KEY_RIGHT] = "Right Arrow";
	validKeys[aie::EInputCodes::INPUT_KEY_UP] = "Up Arrow";
	validKeys[aie::EInputCodes::INPUT_KEY_DOWN] = "Down Arrow";
	validKeys[aie::EInputCodes::INPUT_KEY_ESCAPE] = "Escape";
	validKeys[aie::EInputCodes::INPUT_KEY_ENTER] = "Enter";
	validKeys[aie::EInputCodes::INPUT_KEY_KP_0] = "Keypad 0";
	validKeys[aie::EInputCodes::INPUT_KEY_KP_1] = "Keypad 1";
	validKeys[aie::EInputCodes::INPUT_KEY_KP_2] = "Keypad 2";
	validKeys[aie::EInputCodes::INPUT_KEY_KP_3] = "Keypad 3";
	validKeys[aie::EInputCodes::INPUT_KEY_KP_4] = "Keypad 4";
	validKeys[aie::EInputCodes::INPUT_KEY_KP_5] = "Keypad 5";
	validKeys[aie::EInputCodes::INPUT_KEY_KP_6] = "Keypad 6";
	validKeys[aie::EInputCodes::INPUT_KEY_KP_7] = "Keypad 7";
	validKeys[aie::EInputCodes::INPUT_KEY_KP_8] = "Keypad 8";
	validKeys[aie::EInputCodes::INPUT_KEY_KP_9] = "Keypad 9";
	validKeys[aie::EInputCodes::INPUT_KEY_0] = "0";
	validKeys[aie::EInputCodes::INPUT_KEY_1] = "1";
	validKeys[aie::EInputCodes::INPUT_KEY_2] = "2";
	validKeys[aie::EInputCodes::INPUT_KEY_3] = "3";
	validKeys[aie::EInputCodes::INPUT_KEY_4] = "4";
	validKeys[aie::EInputCodes::INPUT_KEY_5] = "5";
	validKeys[aie::EInputCodes::INPUT_KEY_6] = "6";
	validKeys[aie::EInputCodes::INPUT_KEY_7] = "7";
	validKeys[aie::EInputCodes::INPUT_KEY_8] = "8";
	validKeys[aie::EInputCodes::INPUT_KEY_9] = "9";
	#pragma endregion
}
ControlsState::~ControlsState() {}

void ControlsState::update(float deltaTime) {
	aie::Input* input = aie::Input::getInstance();
	if (input->wasMouseButtonPressed(0)) {
		if (m_back->Collision()) {
			app->getGameStateManager()->popState();
			app->getGameStateManager()->pushState((int)eStateID::MENU);
		}
	}

	if (m_moveForward->Collision() && input->getPressedKeys().size() > 0) {
		int code = input->getPressedKeys()[0];
		if (validKeys.find(code) != -1) {
			app->m_moveForward = code;
			m_moveForward->SetText(validKeys[code]);
		}
	}
	else if (m_moveBackward->Collision() && input->getPressedKeys().size() > 0) {
		int code = input->getPressedKeys()[0];
		if (validKeys.find(code) != -1) {
			app->m_moveBackward = code;
			m_moveBackward->SetText(validKeys[code]);
		}
	}
	else if (m_rotateLeft->Collision() && input->getPressedKeys().size() > 0) {
		int code = input->getPressedKeys()[0];
		if (validKeys.find(code) != -1) {
			app->m_rotateBodyLeft = code;
			m_rotateLeft->SetText(validKeys[code]);
		}
	}
	else if (m_rotateRight->Collision() && input->getPressedKeys().size() > 0) {
		int code = input->getPressedKeys()[0];
		if (validKeys.find(code) != -1) {
			app->m_rotateBodyRight = code;
			m_rotateRight->SetText(validKeys[code]);
		}
	}
	else if (m_rotateBarrelLeft->Collision() && input->getPressedKeys().size() > 0) {
		int code = input->getPressedKeys()[0];
		if (validKeys.find(code) != -1) {
			app->m_rotateBarrelLeft = code;
			m_rotateBarrelLeft->SetText(validKeys[code]);
		}
	}
	else if (m_rotateBarrelRight->Collision() && input->getPressedKeys().size() > 0) {
		int code = input->getPressedKeys()[0];
		if (validKeys.find(code) != -1) {
			app->m_rotateBarrelRight = code;
			m_rotateBarrelRight->SetText(validKeys[code]);
		}
	}
	else if (m_shoot->Collision() && input->getPressedKeys().size() > 0) {
		int code = input->getPressedKeys()[0];
		if (validKeys.find(code) != -1) {
			app->m_shoot = code;
			m_shoot->SetText(validKeys[code]);
		}
	}
	else if (m_pause->Collision() && input->getPressedKeys().size() > 0) {
		int code = input->getPressedKeys()[0];
		if (validKeys.find(code) != -1) {
			app->m_pause = code;
			m_pause->SetText(validKeys[code]);
		}
	}
}

void ControlsState::render(aie::Renderer2D* renderer) {
	m_back->Draw(renderer);

	renderer->setRenderColour(1, 1, 1, 1);

	float t0 = resources.getFont("./font/consolas.ttf", 30)->getStringWidth("CONTROLS");

	float t1 = m_font.get()->getStringWidth("Move Tank Forwards");
	float t11 = m_font.get()->getStringHeight("Move Tank Forwards");

	float t2 = m_font.get()->getStringWidth("Move Tank Backwards");
	float t21 = m_font.get()->getStringHeight("Move Tank Backwards");

	float t3 = m_font.get()->getStringWidth("Rotate Tank Left");
	float t31 = m_font.get()->getStringHeight("Rotate Tank Left");

	float t4 = m_font.get()->getStringWidth("Rotate Tank Right");
	float t41 = m_font.get()->getStringHeight("Rotate Tank Right");

	float t5 = m_font.get()->getStringWidth("Rotate Barrel Left");
	float t51 = m_font.get()->getStringHeight("Rotate Barrel Left");

	float t6 = m_font.get()->getStringWidth("Rotate Barrel Right");
	float t61 = m_font.get()->getStringHeight("Rotate Barrel Right");

	float t7 = m_font.get()->getStringWidth("Shoot");
	float t71 = m_font.get()->getStringHeight("Shoot");

	float t8 = m_font.get()->getStringWidth("Pause");
	float t81 = m_font.get()->getStringHeight("Pause");

	renderer->drawText(resources.getFont("./font/consolas.ttf", 30).get(), "CONTROLS", app->getWindowWidth() / 2 - t0 / 2, app->getWindowHeight() / 4 * 3);
	renderer->drawText(m_font.get(), "Move Tank Forward", app->getWindowWidth() / 2 - t1 / 2, (app->getWindowHeight() / 3 * 2) - (t11 / 2));
	renderer->drawText(m_font.get(), "Move Tank Backward", app->getWindowWidth() / 2 - t2 / 2, (app->getWindowHeight() / 3 * 2) - 35 - (t21 / 2));
	renderer->drawText(m_font.get(), "Rotate Tank Left", app->getWindowWidth() / 2 - t3 / 2, (app->getWindowHeight() / 3 * 2) - 70 - (t31 / 2));
	renderer->drawText(m_font.get(), "Rotate Tank Right", app->getWindowWidth() / 2 - t4 / 2, (app->getWindowHeight() / 3 * 2) - 105 - (t41 / 2));
	renderer->drawText(m_font.get(), "Rotate Barrel Left", app->getWindowWidth() / 2 - t5 / 2, (app->getWindowHeight() / 3 * 2) - 140 - (t51 / 2));
	renderer->drawText(m_font.get(), "Rotate Barrel Right", app->getWindowWidth() / 2 - t6 / 2, (app->getWindowHeight() / 3 * 2) - 175 - (t61 / 2));
	renderer->drawText(m_font.get(), "Shoot", app->getWindowWidth() / 2 - t7 / 2, (app->getWindowHeight() / 3 * 2) - 210 - (t71 / 2));
	renderer->drawText(m_font.get(), "Pause", app->getWindowWidth() / 2 - t8 / 2, (app->getWindowHeight() / 3 * 2) - 245 - (t81 / 2));

	m_moveForward->Draw(renderer);
	m_moveBackward->Draw(renderer);
	m_rotateLeft->Draw(renderer);
	m_rotateRight->Draw(renderer);
	m_rotateBarrelLeft->Draw(renderer);
	m_rotateBarrelRight->Draw(renderer);
	m_shoot->Draw(renderer);
	m_pause->Draw(renderer);
}