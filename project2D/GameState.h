#pragma once
#include "IGameState.h"
#include "RockSpawner.h"
#include "Tank.h"
#include "OBB.h"

enum class Controls { MOVE_FORWARD, MOVE_BACKWARD, ROTATE_TANK_LEFT, ROTATE_TANK_RIGHT, ROTATE_BARREL_LEFT, ROTATE_BARREL_RIGHT, SHOOT_BULLET, PAUSE_GAME };
enum class Level { LEVEL_1 = 10, LEVEL_2 = 15, LEVEL_3 = 20, LEVEL_4 = 25, LEVEL_5 = 30};

class GameState : public IGameState
{
public:
	GameState(Application2D* _app);
	virtual ~GameState();

	virtual void update(float deltaTime);
	virtual void render(aie::Renderer2D* renderer);

private:
	SceneObject*  m_root;
	Tank*         m_tank;

	OBB* worldBounds;

	void loadLevel(Level level);
	int rockCount, bulletCount, bulletCount_d, highScore, gameLevel;
	RockSpawner rockSpawner;
	bool gameOver;
};