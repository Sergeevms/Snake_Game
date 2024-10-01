#include "MainMenuState.h"
#include "Settings.h"

namespace SnakeGame
{
	MainMenuState::MainMenuState() : BaseState(), menu(), inputHandler(&menu)
	{

	}

	void MainMenuState::Draw(sf::RenderWindow& window) const
	{
		menu.Draw(window, sf::Vector2f(Settings::GetSettings()->screenWidth / 2.f, 10.f));
	}

	void MainMenuState::Update(const float deltaTime)
	{

	}

	void MainMenuState::HandleInput(const std::vector<sf::Event>& input)
	{
		inputHandler.HandleInputEvents(input);
	}
}