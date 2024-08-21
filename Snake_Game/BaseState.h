#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Settings.h"

namespace SnakeGame
{
	enum class GameState
	{
		None,
		MainMenu,
		Playing
	}; 
	class Game;

	class BaseState
	{
	public:
		BaseState(Game* currentGame, Settings& settings) : game(currentGame), currentSettings{ settings } { };
		virtual ~BaseState() = default;
		virtual void Draw(sf::RenderWindow&) const = 0;
		virtual void Update(float) = 0;
		virtual void HandleInput(std::vector<sf::Event> const&) = 0;
		virtual GameState GetGameState() const = 0;
	protected:
		Settings& currentSettings;
		Game* game;
	};
}