#pragma once
#include "GameStateManager.h"
#include "IGameState.h"
#include <assert.h>

GameStateManager::GameStateManager()
{
}

GameStateManager::~GameStateManager()
{
	for (auto iter = m_registeredStates.begin(); iter != m_registeredStates.end(); iter++)
		delete iter->value;
	m_registeredStates.clear();
}

void GameStateManager::updateStates(float deltaTime)
{
	processCommands();

	(*m_activeStates.top()).update(deltaTime);
	//for (auto iter = m_activeStates.begin(); iter != m_activeStates.end(); iter++)
		//(*iter)->update(deltaTime);
}

void GameStateManager::renderStates(aie::Renderer2D * renderer)
{
	//(*m_activeStates.rbegin())->render(renderer);
	for (auto iter = m_activeStates.begin(); iter != m_activeStates.end(); iter++)
		(*iter)->render(renderer);
}

void GameStateManager::setState(int id, IGameState * state)
{
	Command command;
	command.cmd = eCommand::SET;
	command.id = id;
	command.state = state;

	m_commands.AddToEnd(command);
}

void GameStateManager::pushState(int id)
{
	Command command;
	command.cmd = eCommand::PUSH;
	command.id = id;
	command.state = nullptr;

	m_commands.AddToEnd(command);
}

void GameStateManager::popState()
{
	Command command;
	command.cmd = eCommand::POP;
	command.id = -1;
	command.state = nullptr;

	m_commands.AddToEnd(command);
}

IGameState* GameStateManager::getTopState()
{
	if (m_activeStates.count() > 0)
		return m_activeStates.top();
	return nullptr;
}

void GameStateManager::processCommands()
{
	for (auto iter = m_commands.begin(); iter != m_commands.end(); iter++)
	{
		Command &c = (*iter);
		switch (c.cmd)
		{
		case eCommand::POP:
			processPopState();
			break;
		case eCommand::PUSH:
			processPushState(c.id);
			break;
		case eCommand::SET:
			processSetState(c.id, c.state);
			break;
		default:
			assert(false && "Command not found!");
			break;
		}
	}

	m_commands.Clear();
}

void GameStateManager::processSetState(int id, IGameState * state)
{
	//auto iter = m_registeredStates.find(id);
	if (m_registeredStates.find(id) != -1)
		m_registeredStates.remove(id); // Delete the state if it already exists

							 // Replace it with the new state
	m_registeredStates[id] = state;
}

void GameStateManager::processPushState(int id)
{
	auto iter = m_registeredStates.find(id);
	if (iter != -1)
		m_activeStates.push(m_registeredStates[id]); // If the state exists, add it to the list of active states
	else
		assert((int)id && "State not found!"); // if not, crash
}

void GameStateManager::processPopState()
{
	if (m_activeStates.count() > 0)
		m_activeStates.pop();
}
