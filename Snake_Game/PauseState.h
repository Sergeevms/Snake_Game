#pragma once
#include "BaseState.h"
#include "PauseMenu.h"
#include "PauseStateInputHandler.h"

namespace  SnakeGame
{
	class PauseState : public BaseState
	{
	public:
		PauseState(Game* currentGame, Settings& settings);
		virtual ~PauseState() = default;
		virtual void Draw(sf::RenderWindow& window) const  override;
		virtual void Update(float deltaTime)  override;
		virtual void HandleInput(std::vector<sf::Event> const& input)  override;
		//virtual GameState GetGameState() const  override { return GameState::Pause; };
	private:
		sf::RectangleShape overallBackground;
		sf::RectangleShape menuBackground;
		sf::Vector2f menuPosition;
		PauseMenu menu;
		PauseStateInputHandler inputHandler;
	};
}

