#include "MainMenuInputHandler.h"
#include "MainMenu.h"
#include "Settings.h"
#include "Game.h"
#include "BaseState.h"

namespace SnakeGame
{
	MainMenuInputHandler::MainMenuInputHandler(MainMenu* currentMenu) : BaseMenuInputHandler(currentMenu), menu(currentMenu)
	{
		activateMapping[MenuNodeActivateReaction::Exit] = [this](BaseInputHandler* handler)
			{if (auto currentHandler = dynamic_cast<MainMenuInputHandler*>(this)) { currentHandler->ExitGame(); }};
		activateMapping[MenuNodeActivateReaction::Play] = [this](BaseInputHandler* handler)
			{if (auto currentHandler = dynamic_cast<MainMenuInputHandler*>(this)) { currentHandler->StartPlaying(); }};
		activateMapping[MenuNodeActivateReaction::SwitchMusic] = [this](BaseInputHandler* handler)
			{ if (auto currentHandler = dynamic_cast<MainMenuInputHandler*>(this)) { currentHandler->SwitchMusic(); }};
		activateMapping[MenuNodeActivateReaction::SwitchSound] = [this](BaseInputHandler* handler)
			{ if (auto currentHandler = dynamic_cast<MainMenuInputHandler*>(this)) { currentHandler->SwitchSound(); }};
		activateMapping[MenuNodeActivateReaction::SwitchDifficulty] = [this](BaseInputHandler* handler)
			{ if (auto currentHandler = dynamic_cast<MainMenuInputHandler*>(this)) { currentHandler->SwitchDifficulty(); }};
	}

	void MainMenuInputHandler::ExitGame()
	{
		Game::GetGame()->ShutDown();
	}

	void MainMenuInputHandler::StartPlaying()
	{
		Game::GetGame()->SwitchToState(GameState::Playing);
	}

	void MainMenuInputHandler::SwitchMusic()
	{
		Settings* settings = Settings::GetSettings();
		settings->musicOn = !settings->musicOn;
		menu->UpdateChecked(settings->musicOn);
	}

	void MainMenuInputHandler::SwitchSound()
	{
		Settings* settings = Settings::GetSettings();
		settings->soundOn = !settings->soundOn;
		menu->UpdateChecked(settings->soundOn);
	}

	void MainMenuInputHandler::SwitchDifficulty()
	{
		Settings* settings = Settings::GetSettings();
		settings->UpdateDifficulty(menu->GetSelectedDifficulty());
		menu->UpdateChecked(true);
	}
}