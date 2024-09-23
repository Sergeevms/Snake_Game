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
		virtual void Update(float deltaTime) override;
		virtual void HandleInput(std::vector<sf::Event> const& input) override;
		//virtual GameState GetGameState() const  override { return GameState::MainMenu; };
	private:
		MainMenu menu;
		MainMenuInputHandler inputHandler;
	};

}