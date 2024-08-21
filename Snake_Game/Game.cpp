#include "Game.h"
#include "PlayingState.h"

namespace SnakeGame
{
	Game::Game()
	{		
		stateStack.push_back(std::make_shared<PlayingState>(this, currentSettings));
	}

	bool Game::IsGameShuttingDown() const
	{
		return false;
	}

	void Game::Update(float deltaTime, std::vector<sf::Event> const& inputEvents)
	{
		(*stateStack.rbegin())->HandleInput(inputEvents);
		(*stateStack.rbegin())->Update(deltaTime);
	}

	void Game::Draw(sf::RenderWindow& window) const
	{
		(*stateStack.rbegin())->Draw(window);
	}
}