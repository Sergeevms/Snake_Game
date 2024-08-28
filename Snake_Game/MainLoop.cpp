#include <SFML/Graphics.hpp>
#include <vector>
#include "MainLoop.h"
#include "Settings.h"


namespace SnakeGame
{
	MainLoop::MainLoop()
	{
		window = new sf::RenderWindow(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), sf::String::fromUtf16(GAME_NAME.begin(), GAME_NAME.end()));
		game = new Game();
	}

	MainLoop::~MainLoop()
	{
		if (window)
		{
			delete window;
		}

		if (game)
		{
			delete game;
		}
	}

	void MainLoop::Run()
	{
		sf::Clock clock;
		float lastTime = clock.getElapsedTime().asSeconds();

		while (window->isOpen())
		{
			//sf::sleep(sf::milliseconds(1));
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
		}
	}
}