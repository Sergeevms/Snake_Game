#pragma once
#include "BaseState.h"
#include "MainMenu.h"
#include "MainMenuInputHandler.h"

namespace SnakeGame
{
	class MainMenuState : public BaseState
	{
	public:
		MainMenuState(Game* currentGame, Settings& settings);
		virtual ~MainMenuState() = default;
		virtual void Draw(sf::RenderWindow& window) const override;
		virtual void Update(const float deltaTime) override;
		virtual void HandleInput(const std::vector<sf::Event>& input) override;
	private:
		MainMenu menu;
		MainMenuInputHandler inputHandler;
	};

}
