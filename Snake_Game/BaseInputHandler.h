#pragma once
#include <vector>
#include <SFML/Graphics.hpp>

namespace SnakeGame
{
	enum class ActionsTypesOnInput
	{
		Up,
		Right,
		Down,
		Left,
		Back,
		Forward,
		Pause
	};

	class Game;
	struct Settings;

	class BaseInputHandler
	{
	public:
		BaseInputHandler(Game* currentGame, Settings& currentSettings) : game(currentGame), settings(currentSettings) {};
		virtual void HandleInputEvents(const std::vector<sf::Event>& input) = 0;
		virtual ~BaseInputHandler() = default;
	protected:
		Game* game;
		Settings& settings;
	};
}

