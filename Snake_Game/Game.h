#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Settings.h"
#include "BaseState.h"

namespace SnakeGame
{
	class Game
	{
	public:
		Game();
		bool IsGameShuttingDown() const;
		void Update(float deltaTime, std::vector <sf::Event> const& inputEvents);
		void Draw(sf::RenderWindow&) const;
	private:
		Settings currentSettings;
		std::vector<std::shared_ptr<BaseState>> stateStack;
	};
}