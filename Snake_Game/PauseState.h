#pragma once
#include "BaseState.h"
#include "PauseMenu.h"
#include "PauseStateInputHandler.h"

namespace  SnakeGame
{
	class PauseState : public BaseState
	{
	public:
		PauseState();
		virtual ~PauseState() = default;
		virtual void Draw(sf::RenderWindow& window) const  override;
		virtual void Update(const float deltaTime)  override;
		virtual void HandleInput(const std::vector<sf::Event>& input)  override;
	private:
		sf::RectangleShape overallBackground;
		sf::RectangleShape menuBackground;
		sf::Vector2f menuPosition;
		PauseMenu menu;
		PauseStateInputHandler inputHandler;
	};
}

