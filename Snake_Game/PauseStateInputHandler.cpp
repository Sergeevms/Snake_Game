#include "PauseStateInputHandler.h"
#include "PauseMenu.h"
#include "Game.h"

namespace SnakeGame
{
	PauseStateInputHandler::PauseStateInputHandler(Game* currentGame, Settings& currentSettings, PauseMenu* currentMenu) :
		BaseInputHandler(currentGame, currentSettings), menu(currentMenu)
	{
		actionMapping[ActionsTypesOnInput::Up] = &PauseStateInputHandler::selectPrevious;
		actionMapping[ActionsTypesOnInput::Down] = &PauseStateInputHandler::selectNext;
		actionMapping[ActionsTypesOnInput::Forward] = &PauseStateInputHandler::activateCurrent;
		actionMapping[ActionsTypesOnInput::Back] = &PauseStateInputHandler::returnToGame;

		activateMapping[ActivateReactionPauseMenu::MainMenu] = &PauseStateInputHandler::returnToMenu;
		activateMapping[ActivateReactionPauseMenu::Play] = &PauseStateInputHandler::returnToGame;
	}

	void PauseStateInputHandler::HandleInputEvents(std::vector<sf::Event> const& input)
	{
		for (auto& inputEvent : input)
		{
			if (settings.keyMap.contains(inputEvent.key.code))
			{
				if (actionMapping.contains(settings.keyMap.at(inputEvent.key.code)))
				{
					game->PlaySound(soundType::OnKeyHit);
					std::invoke(actionMapping[settings.keyMap[inputEvent.key.code]], this);
				}
			}
		}
	}

	void PauseStateInputHandler::selectNext()
	{
		menu->SelectNext();
	}

	void PauseStateInputHandler::selectPrevious()
	{
		menu->SelectPrevious();
	}

	void PauseStateInputHandler::activateCurrent()
	{
		std::invoke(activateMapping[menu->GetReaction()], this);
	}

	void PauseStateInputHandler::returnToGame()
	{
		game->SwitchToState(GameState::Playing);
	}

	void PauseStateInputHandler::returnToMenu()
	{
		game->SwitchToState(GameState::MainMenu);
	}
}