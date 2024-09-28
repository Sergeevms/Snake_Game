#include "PauseStateInputHandler.h"
#include "PauseMenu.h"
#include "Game.h"
#include "Settings.h"
#include "BaseState.h"

namespace SnakeGame
{
	PauseStateInputHandler::PauseStateInputHandler(Game* currentGame, Settings& currentSettings, PauseMenu* currentMenu) :
		BaseMenuInputHandler(currentGame, currentSettings, currentMenu)
	{	actionMapping[ActionsTypesOnInput::Back] = [this](BaseInputHandler* handler)
		{if (auto currentHandler = dynamic_cast<PauseStateInputHandler*>(this)) { currentHandler->returnToGame(); }};

		activateMapping[MenuNodeActivateReaction::MainMenu] = [this](BaseInputHandler* handler)
			{if (auto currentHandler = dynamic_cast<PauseStateInputHandler*>(this)) { currentHandler->returnToMenu(); }};
		activateMapping[MenuNodeActivateReaction::Play] = [this](BaseInputHandler* handler)
			{if (auto currentHandler = dynamic_cast<PauseStateInputHandler*>(this)) { currentHandler->returnToGame(); }};
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