#include "MainMenuInputHandler.h"
#include "MainMenu.h"
#include "Settings.h"
#include "Game.h"

namespace SnakeGame
{
	MainMenuInputHandler::MainMenuInputHandler(Game* currentGame, Settings & currentSettings, MainMenu* currentMenu) : BaseInputHandler(currentGame, currentSettings), menu(currentMenu)
	{
		actionMapping[ActionsTypesOnInput::Up] = &MainMenuInputHandler::SelectPrevious;
		actionMapping[ActionsTypesOnInput::Down] = &MainMenuInputHandler::SelectNext;
		actionMapping[ActionsTypesOnInput::Forward] = &MainMenuInputHandler::ActivateCurrent;
		actionMapping[ActionsTypesOnInput::Back] = &MainMenuInputHandler::GoBack;

		activateMapping[ActivateReactionMainMenu::Exit] = &MainMenuInputHandler::ExitGame;
		activateMapping[ActivateReactionMainMenu::Play] = &MainMenuInputHandler::StartPlaying;
		activateMapping[ActivateReactionMainMenu::SwitchMusic] = &MainMenuInputHandler::SwitchMusic;
		activateMapping[ActivateReactionMainMenu::SwitchSound] = &MainMenuInputHandler::SwitchSound;
	}

	void MainMenuInputHandler::HandleInputEvents(std::vector<sf::Event> const& input)
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

	void MainMenuInputHandler::SelectNext()
	{
		menu->SelectNext();
	}

	void MainMenuInputHandler::SelectPrevious()
	{
		menu->SelectPrevious();
	}

	void MainMenuInputHandler::ActivateCurrent()
	{
		if (!menu->ExpandSelected())
		{
			std::invoke(activateMapping[menu->GetReaction()], this);
		}
	}

	void MainMenuInputHandler::GoBack()
	{
		menu->ReturnToPrevious();
	}

	void MainMenuInputHandler::ExitGame()
	{
		game->ShutDown();
	}

	void MainMenuInputHandler::StartPlaying()
	{
		game->SwitchToState(GameState::Playing);
	}

	void MainMenuInputHandler::SwitchMusic()
	{
		settings.musicOn = !settings.musicOn;
		menu->UpdateChecked(settings.musicOn);
	}

	void MainMenuInputHandler::SwitchSound()
	{
		settings.soundOn = !settings.soundOn;
		menu->UpdateChecked(settings.soundOn);
	}
}