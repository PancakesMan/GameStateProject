#include "GameState.h"
#include "GameOverState.h"

GameState::GameState(Application2D* _app) : IGameState(_app)
{
	worldBounds = new OBB(Vector2<float>(app->getWindowWidth() / 2, (app->getWindowHeight() - 50) / 2), Vector2<float>(app->getWindowWidth(), app->getWindowHeight() - 50));

	loadLevel(Level::LEVEL_1);
	gameOver = false;
	highScore = 0;
}

GameState::~GameState()
{
	//delete m_tank;
	//delete m_root;
}

void GameState::update(float deltaTime)
{
	aie::Input* input = aie::Input::getInstance();

	if (input->wasKeyPressed(app->m_pause)) {
		app->getGameStateManager()->pushState((int)eStateID::PAUSE);
	}

	if (input->isKeyDown(app->m_moveForward)) {
		m_tank->moveForward();
	}

	if (input->isKeyDown(app->m_moveBackward)) {
		m_tank->moveBackwards();
	}

	if (input->isKeyDown(app->m_rotateBodyLeft)) {
		m_tank->rotate(0.5f * deltaTime);
	}

	if (input->isKeyDown(app->m_rotateBodyRight)) {
		m_tank->rotate(-0.5f * deltaTime);
	}

	if (input->wasKeyPressed(app->m_shoot)) {
		if (bulletCount > 0) {
			m_tank->fire();
			bulletCount--;
		}
	}

	if (input->isKeyDown(app->m_rotateBarrelLeft)) {
		m_tank->rotateBarrel(0.5f * deltaTime);
	}

	if (input->isKeyDown(app->m_rotateBarrelRight)) {
		m_tank->rotateBarrel(-0.5f * deltaTime);
	}

	if ((bulletCount == 0 && bulletCount_d == 0) || m_tank->isDestroyed())
		gameOver = true;

	if (rockCount == 0) {
		highScore += bulletCount * 10;
		if (gameLevel == 5) {
			gameOver = true;
			GameOverState::message = "CONGRATULATIONS! YOU WON!";
		}
		else loadLevel(Level(gameLevel * 5 + 10));
	}

	if (gameOver) {
		GameOverState::score = highScore;

		app->getGameStateManager()->popState();
		app->getGameStateManager()->pushState((int)eStateID::GAME_OVER);
	}

	// Get all objects under the scene root
	DynamicArray<SceneObject*> objs = m_root->getChildrenRecursively();

	// Loop through all objects in the scene
	for (int i = 0; i < objs.Size(); i++) {

		// If an object leaves the screen
		// Destroy it
		SpriteObject* so = dynamic_cast<SpriteObject*>(objs[i]);
		if (so != nullptr)
			if (!worldBounds->contains(so)) {
				so->destroy();
				if (dynamic_cast<Bullet*>(so) != nullptr)
					bulletCount_d--;
			}

		// Check if object is a bullet
		Bullet* obj = dynamic_cast<Bullet*>(objs[i]);
		if (obj != nullptr)
		{
			// If it is a bullet, check if it hits something
			for (size_t j = 0; j < objs.Size(); j++)
			{
				// Check all rock objects
				Rock* rockObj = dynamic_cast<Rock*>(objs[j]);
				if (rockObj != nullptr)
				{
					// If object is a rock, check if it was hit by the bullet
					OBB rockOBB = OBB(rockObj);
					OBB bulletOBB = OBB(obj);
					if (bulletOBB.collides(rockOBB))
					{
						// If they collided, destroy them both
						obj->destroy();
						bulletCount_d--;

						// Increase highScore by 10
						highScore += 10;
						rockObj->destroy();
						if (rockObj->isDestroyed()) rockCount--;
					}
				}
			}
		}

		// Check all rock objects
		Rock* rockObj = dynamic_cast<Rock*>(objs[i]);
		if (rockObj != nullptr)
		{
			// Get all objects under the tank
			DynamicArray<SceneObject*> tankParts = m_tank->getChildrenRecursively();
			for (size_t k = 0; k < tankParts.Size(); k++)
			{
				// Check if the object is a sprite and it's not a bullet
				SpriteObject* tankPart = dynamic_cast<SpriteObject*>(tankParts[k]);
				bool objIsBullet = dynamic_cast<Bullet*>(tankPart) != nullptr;
				if (tankPart != nullptr && !objIsBullet)
				{
					// If the tank body or barrell collides with the rock
					// destroy them both
					if (OBB(rockObj).collides(OBB(tankPart)))
					{
						m_tank->destroy();
						//rockObj->destroy();
					}
				}
			}
		}
	}

	m_root->update(deltaTime);
}

void GameState::render(aie::Renderer2D* renderer)
{
	renderer->setRenderColour(0.15f, 0.65f, 0, 1);
	renderer->drawBox(app->getWindowWidth() / 2, (app->getWindowHeight() - 50) / 2, app->getWindowWidth(), app->getWindowHeight() - 50, 0, 100);

	renderer->setRenderColour(1, 1, 1, 1);
	m_root->draw(renderer);
	worldBounds->draw(renderer);

	std::string levelText = "Level: " + std::to_string(gameLevel);
	float levelWidth = m_font.get()->getStringWidth(levelText.c_str());
	renderer->drawText(m_font.get(), levelText.c_str(), levelWidth / 2, app->getWindowHeight() - 30);

	std::string bulletText = "Bullets: " + std::to_string(bulletCount);
	//float bulletWidth = m_font.get()->getStringWidth(bulletText.c_str());
	renderer->drawText(m_font.get(), bulletText.c_str(), app->getWindowWidth() - 150, app->getWindowHeight() - 30);

	std::string scoreText = "Score: " + std::to_string(highScore);
	float scoreWidth = m_font.get()->getStringWidth(scoreText.c_str());
	renderer->drawText(m_font.get(), scoreText.c_str(), app->getWindowWidth() / 2 - scoreWidth / 2, app->getWindowHeight() - 30);
}

void GameState::loadLevel(Level level) {
	m_root = new SceneObject();
	m_tank = new Tank(TankColor::Red, app->getWindowWidth() / 2, (app->getWindowHeight() - 50) / 2);
	m_root->addChild(m_tank);

	for (int i = 0; i < (int)level; i++)
		m_root->addChild(rockSpawner.getRandomSizedRock(35, app->getWindowWidth() - 35, 35, app->getWindowHeight() - 85));

	rockCount = (int)level;
	bulletCount = rockCount * 3;
	bulletCount_d = bulletCount;
	gameLevel = (rockCount - 5) / 5;

	DynamicArray<SceneObject*> objs = m_root->getChildrenRecursively();
	for (size_t i = 0; i < objs.Size(); i++) {
		// Check all rock objects
		Rock* rockObj = dynamic_cast<Rock*>(objs[i]);
		if (rockObj != nullptr)
		{
			// Get all objects under the tank
			DynamicArray<SceneObject*> tankParts = m_tank->getChildrenRecursively();
			for (size_t k = 0; k < tankParts.Size(); k++)
			{
				// Check if the object is a sprite and it's not a bullet
				SpriteObject* tankPart = dynamic_cast<SpriteObject*>(tankParts[k]);
				bool objIsBullet = dynamic_cast<Bullet*>(tankPart) != nullptr;
				if (tankPart != nullptr && !objIsBullet)
					// If the tank body or barrell collides with the rock
					// destroy them both
					if (OBB(rockObj).collides(OBB(tankPart)))
						m_tank->destroy();
			}
		}
	}

	// If the tank died by a rock spawning on top of it
	// Reload the level
	if (m_tank->isDestroyed()) {
		delete m_root;
		m_root = new SceneObject();
		loadLevel(level);
	}
}