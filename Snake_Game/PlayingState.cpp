#include "PlayingState.h"

namespace SnakeGame
{
	PlayingState::PlayingState(Settings& settings) : BaseState(settings), map(settings), snake(settings)
	{		
		map.LoadFromFile(settings.selectedLevel);
		map.CreateSavedLvl();
		snake.LoadFromCharMap(map.getcharMap(), map.getSnakeHeadPosition());
	}

	void PlayingState::Draw(sf::RenderWindow& window) const
	{
		map.Draw(window);
		snake.Draw(window);
	}

	void PlayingState::Update(const float deltaTime)
	{
		snake.Update(deltaTime);
	}

	void PlayingState::HandleInput(std::vector<sf::Event> const& inputEvents)
	{
	}
}