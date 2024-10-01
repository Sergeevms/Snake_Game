#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

namespace SnakeGame
{
	enum class GameState
	{
		None,
		MainMenu,
		Playing,
		Pause
	}; 

	class Game;
	struct Settings;

	class BaseState
	{
	public:
		BaseState() {};
		virtual ~BaseState() = default;
		virtual void Draw(sf::RenderWindow&) const = 0;
		virtual void Update(const float) = 0;
		virtual void HandleInput(const std::vector<sf::Event>&) = 0;
	};
}