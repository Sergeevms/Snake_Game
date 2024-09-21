#include "MainMenuState.h"

namespace SnakeGame
{
	MainMenuState::MainMenuState(Game* currentGame, Settings& settings) :
		BaseState(currentGame, settings), menu(settings), inputHandler(currentGame, settings, &menu)
	{

	}

	void MainMenuState::Draw(sf::RenderWindow& window) const
	{
		menu.Draw(window, sf::Vector2f(SCREEN_WIDTH / 2.f, 10.f));
	}

	void MainMenuState::Update(float deltaTime)
	{

	}

	void MainMenuState::HandleInput(std::vector<sf::Event> const& input)
	{
		inputHandler.HandleInputEvents(input);
	}
}