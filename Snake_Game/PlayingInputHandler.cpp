#include <functional>
#include "PlayingInputHandler.h"

SnakeGame::PlayingInputHandler::PlayingInputHandler(Game* currentGame, Settings & currentSettings, Snake* currentSnake) : BaseInputHandler(currentGame, currentSettings), snake(currentSnake)
{
	actionMapping[ActionsTypesOnInput::Up] = &PlayingInputHandler::turnSnakeUp;
	actionMapping[ActionsTypesOnInput::Down] = &PlayingInputHandler::turnSnakeDown;
	actionMapping[ActionsTypesOnInput::Left] = &PlayingInputHandler::turnSnakeLeft;
	actionMapping[ActionsTypesOnInput::Right] = &PlayingInputHandler::turnSnakeRight;
};

void SnakeGame::PlayingInputHandler::HandleInputEvents(std::vector<sf::Event> const& input)
{
	for (auto& inputEvent : input)
	{
		if (settings.keyMap.contains(inputEvent.key.code))
		{
			if (actionMapping.contains(settings.keyMap[inputEvent.key.code]))
			{
				std::invoke(actionMapping[settings.keyMap[inputEvent.key.code]], this);
			}
		}
	}
}

void SnakeGame::PlayingInputHandler::turnSnakeUp()
{
	snake->SetNewDirection(Direction::Up);
}

void SnakeGame::PlayingInputHandler::turnSnakeRight()
{
	snake->SetNewDirection(Direction::Rigth);
}

void SnakeGame::PlayingInputHandler::turnSnakeDown()
{
	snake->SetNewDirection(Direction::Down);
}

void SnakeGame::PlayingInputHandler::turnSnakeLeft()
{
	snake->SetNewDirection(Direction::Left);
}
