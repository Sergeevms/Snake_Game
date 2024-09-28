#include <SFML/Graphics.hpp>
#include <vector>
#include "MainLoop.h"
#include "Settings.h"


namespace SnakeGame
{
	MainLoop::MainLoop()
	{
		window = std::make_unique<sf::RenderWindow>(sf::VideoMode(settings.screenWidth, settings.screenHeight), settings.gameName);
		game = std::make_unique<Game>(settings);
	}

	void MainLoop::Run()
	{
		sf::Clock clock;
		float lastTime = clock.getElapsedTime().asSeconds();

		while (window->isOpen())
		{		
			std::vector<sf::Event> inputEvents;
			sf::Event event;
			while (window->pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
				{
					window->close();
				}
				if (event.type == sf::Event::KeyPressed)
				{
					inputEvents.push_back(event);
				}
			}

			float currentTime = clock.getElapsedTime().asSeconds();
			float deltaTime = currentTime - lastTime;
			lastTime = currentTime;

			game->Update(deltaTime, inputEvents);
			
			window->clear();
			game->Draw(*window);
			window->display();

			if (game->IsGameShuttingDown())
			{
				window->close();
			}
		}
	}
}