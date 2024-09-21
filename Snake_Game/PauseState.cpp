#include "PauseState.h"
#include "Utility.h"

namespace SnakeGame
{
	PauseState::PauseState(Game* currentGame, Settings& settings) : 
		BaseState(currentGame, settings), menu(settings), inputHandler(currentGame, settings, &menu)
	{
		overallBackground.setPosition(relativePositions.at(RelativePosition::TopLeft));
		overallBackground.setSize({ SCREEN_WIDTH, SCREEN_HEIGHT });
		overallBackground.setFillColor({255, 255, 255, 125});

		menuBackground.setSize({ SCREEN_WIDTH / 4.f, SCREEN_HEIGHT / 2.f });
		SetOriginByRelative(menuBackground, relativePositions.at(RelativePosition::Center));
		menuBackground.setPosition({ SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f });
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

	void PauseState::HandleInput(std::vector<sf::Event> const& input)
	{
		inputHandler.HandleInputEvents(input);
	}
}