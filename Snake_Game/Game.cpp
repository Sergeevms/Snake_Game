#include "Game.h"
#include "PlayingState.h"
#include "MainMenuState.h"
#include "PauseState.h"

namespace SnakeGame
{
	Game::Game()
	{		
		stateStack.push_back(std::make_shared<MainMenuState>(this, currentSettings));
	}

	bool Game::IsGameShuttingDown() const
	{
		return isShuttingDown;
	}

	void Game::Update(float deltaTime, std::vector<sf::Event> const& inputEvents)
	{
		(*stateStack.rbegin())->HandleInput(inputEvents);
		(*stateStack.rbegin())->Update(deltaTime);
	}

	void Game::Draw(sf::RenderWindow& window) const
	{
		for (auto& state : stateStack)
		{
			state->Draw(window);
		}
	}

	void Game::SwitchToState(GameState newState)
	{
		switch (newState)
		{
		case GameState::MainMenu:
		{
			stateStack.clear();
			stateStack.push_back(std::make_shared<MainMenuState>(this, currentSettings));
			break;
		}
		case GameState::Playing:
		{
			if (std::dynamic_pointer_cast<PauseState>(stateStack.back()))
			{
				stateStack.pop_back();
			}
			else
			{
				stateStack.clear();
				stateStack.push_back(std::make_shared<PlayingState>(this, currentSettings));
			}
			break;
		}
		case GameState::Pause:
		{
			stateStack.push_back(std::make_shared<PauseState>(this, currentSettings));
			break;
		}
		}
	}

	void Game::ShutDown()
	{
		isShuttingDown = true;
	}
}