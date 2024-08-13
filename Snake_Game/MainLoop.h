#pragma once
#include <SFML/Graphics.hpp>
#include "Game.h"

namespace SnakeGame
{
	class MainLoop
	{
	public:
		MainLoop();
		~MainLoop();
		void Run();
	private:
		sf::RenderWindow* window{ nullptr };
		Game* game{ nullptr };
	};

}
