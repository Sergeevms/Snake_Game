#include "PauseState.h"
#include "Utility.h"
#include "Settings.h"

namespace SnakeGame
{
	PauseState::PauseState(Game* currentGame, Settings& settings) : 
		BaseState(currentGame, settings), menu(settings), inputHandler(currentGame, settings, &menu)
	{
		overallBackground.setPosition(relativePositions.at(RelativePosition::TopLeft));
		overallBackground.setSize({ static_cast<float>(settings.screenWidth), static_cast<float>(settings.screenHeight) });
		overallBackground.setFillColor({255, 255, 255, 125});

		menuBackground.setSize({ settings.screenWidth / 4.f, settings.screenHeight / 2.f });
		SetOriginByRelative(menuBackground, relativePositions.at(RelativePosition::Center));
		menuBackground.setPosition({ settings.screenWidth / 2.f, settings.screenHeight / 2.f });
		menuBackground.setFillColor(sf::Color::Black);
		menuBackground.setOutlineColor(sf::Color::White);
		menuBackground.setOutlineThickness(-3.f);

		menuPosition.x = menuBackground.getGlobalBounds().left + menuBackground.getGlobalBounds().width / 2.f;
		menuPosition.y = menuBackground.getGlobalBounds().top + 10.f;
	}

	void PauseState::Draw(sf::RenderWindow& window) const
	{
		window.draw(overallBackground);
		window.draw(menuBackground);
		menu.Draw(window, menuPosition);
	}

	void PauseState::Update(float deltaTime)
	{

	}

	void PauseState::HandleInput(const std::vector<sf::Event>& input)
	{
		inputHandler.HandleInputEvents(input);
	}
}