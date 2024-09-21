#pragma once
#include <vector>
#include <unordered_map>
#include <SFML/Graphics.hpp>
#include "BaseInputHandler.h"

namespace SnakeGame
{
	class PlayingInputHandler;
	typedef void (PlayingInputHandler::*InputReaction)();

	class Game;
	class Snake;
	class PlayingState;
	struct Settings;

	class PlayingInputHandler : public BaseInputHandler
	{
	public:
		PlayingInputHandler(Game* currentGame, Settings & currentSettings, Snake* currentSnake, PlayingState* currentState);
		void HandleInputEvents(std::vector<sf::Event> const& input) override;
	private:
		Snake* snake;
		PlayingState* state;
		std::unordered_map<ActionsTypesOnInput, InputReaction> actionMapping;
		void turnSnakeUp();
		void turnSnakeRight();
		void turnSnakeDown();
		void turnSnakeLeft();
		void pauseGame();
	};
}