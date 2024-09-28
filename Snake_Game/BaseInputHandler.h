#pragma once
#include <vector>
#include <functional>
#include <SFML/Graphics.hpp>
#include <unordered_map>

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
	class BaseInputHandler;
	typedef std::function<void(BaseInputHandler*)> HandlerAction;

	class BaseInputHandler
	{
	public:
		BaseInputHandler(Game* currentGame, Settings& currentSettings) : game(currentGame), settings(currentSettings) {};
		virtual void HandleInputEvents(const std::vector<sf::Event>& input);
		virtual ~BaseInputHandler() = default;
	protected:
		Game* game;
		Settings& settings;
		std::unordered_map<ActionsTypesOnInput, HandlerAction> actionMapping;
	};
}

