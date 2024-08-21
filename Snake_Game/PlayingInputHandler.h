#pragma once
#include <vector>
#include <unordered_map>
#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Snake.h"

namespace SnakeGame
{
	class PlayingInputHandler;
	typedef void (PlayingInputHandler::*InputReaction)();

	class PlayingInputHandler : public BaseInputHandler
	{
	public:
		PlayingInputHandler(Game* currentGame, Settings & currentSettings, Snake* currentSnake);
		void HandleInputEvents(std::vector<sf::Event> const& input) override;
	private:
		Snake* snake;
		std::unordered_map<ActionsTypesOnInput, InputReaction> actionMapping;
		void turnSnakeUp();
		void turnSnakeRight();
		void turnSnakeDown();
		void turnSnakeLeft();
	};
}