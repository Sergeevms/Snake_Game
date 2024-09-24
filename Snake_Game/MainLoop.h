#pragma once
#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Settings.h"

namespace SnakeGame
{
	class MainLoop
	{
	public:
		MainLoop();
		~MainLoop() = default;
		void Run();
	private:		
		Settings settings;
		std::unique_ptr<sf::RenderWindow> window;
		std::unique_ptr<Game> game;
	};

}
