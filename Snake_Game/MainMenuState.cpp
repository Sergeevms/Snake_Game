#include "MainMenuState.h"
#include "Settings.h"

namespace SnakeGame
{
	MainMenuState::MainMenuState(Game* currentGame, Settings& settings) :
		BaseState(currentGame, settings), menu(settings), inputHandler(currentGame, settings, &menu)
	{

	}

	void MainMenuState::Draw(sf::RenderWindow& window) const
	{
		menu.Draw(window, sf::Vector2f(settings.screenWidth / 2.f, 10.f));
	}

	void MainMenuState::Update(const float deltaTime)
	{

	}

	void MainMenuState::HandleInput(const std::vector<sf::Event>& input)
	{
		inputHandler.HandleInputEvents(input);
	}
}