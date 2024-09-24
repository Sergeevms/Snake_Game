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
		BaseState(Game* currentGame, Settings& currentSettings) : game(currentGame), settings{ currentSettings } { };
		virtual ~BaseState() = default;
		virtual void Draw(sf::RenderWindow&) const = 0;
		virtual void Update(float) = 0;
		virtual void HandleInput(std::vector<sf::Event> const&) = 0;
	protected:
		Settings& settings;
		Game* game;
	};
}