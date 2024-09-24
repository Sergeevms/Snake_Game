#include <functional>
#include "PlayingInputHandler.h"
#include "PlayingState.h"
#include "Game.h"
#include "Snake.h"
#include "Settings.h"

namespace SnakeGame
{
	PlayingInputHandler::PlayingInputHandler(Game* currentGame, Settings& currentSettings, Snake* currentSnake, PlayingState* currentState)
		: BaseInputHandler(currentGame, currentSettings), snake(currentSnake), state(currentState)
	{
		actionMapping[ActionsTypesOnInput::Up] = &PlayingInputHandler::turnSnakeUp;
		actionMapping[ActionsTypesOnInput::Down] = &PlayingInputHandler::turnSnakeDown;
		actionMapping[ActionsTypesOnInput::Left] = &PlayingInputHandler::turnSnakeLeft;
		actionMapping[ActionsTypesOnInput::Right] = &PlayingInputHandler::turnSnakeRight;

		actionMapping[ActionsTypesOnInput::Pause] = &PlayingInputHandler::pauseGame;
	};

	void PlayingInputHandler::HandleInputEvents(const std::vector<sf::Event>& input)
	{
		for (auto& inputEvent : input)
		{
			if (settings.keyMap.contains(inputEvent.key.code))
			{
				if (actionMapping.contains(settings.keyMap[inputEvent.key.code]))
				{
					game->PlaySound(SoundType::OnKeyHit);
					std::invoke(actionMapping[settings.keyMap[inputEvent.key.code]], this);
				}
			}
		}
	}

	void PlayingInputHandler::turnSnakeUp()
	{
		snake->SetNewDirection(Direction::Up);
	}

	void PlayingInputHandler::turnSnakeRight()
	{
		snake->SetNewDirection(Direction::Rigth);
	}

	void PlayingInputHandler::turnSnakeDown()
	{
		snake->SetNewDirection(Direction::Down);
	}

	void PlayingInputHandler::turnSnakeLeft()
	{
		snake->SetNewDirection(Direction::Left);
	}

	void PlayingInputHandler::pauseGame()
	{
		state->resetMovingDelay();
		game->SwitchToState(GameState::Pause);
	}
}