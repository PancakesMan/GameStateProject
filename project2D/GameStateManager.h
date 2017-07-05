#pragma once
//#include <map>
#include "Map.h"
#include <vector>
#include "ResourceManager.h"

enum class eStateID {SPLASH, MENU, CONTROLS, GAME, PAUSE, GAME_OVER, SCORES};
class IGameState;

namespace aie
{
	class Renderer2D;
}

class GameStateManager
{
public:
	GameStateManager();
	~GameStateManager();

	void updateStates(float deltaTime);
	void renderStates(aie::Renderer2D* renderer);
	void setState(int id, IGameState* state);
	void pushState(int id);
	void popState();

private:
	Map<int, IGameState*> m_registeredStates;
	DynamicArray<IGameState*> m_activeStates;

	IGameState* getTopState();

	void processCommands();
	void processSetState(int id, IGameState* state);
	void processPushState(int id);
	void processPopState();

	enum class eCommand { SET, PUSH, POP };
	struct Command
	{
		eCommand cmd;
		int id;
		IGameState* state;
	};

	DynamicArray<Command> m_commands;
};

