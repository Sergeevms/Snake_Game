#pragma once
#include <unordered_map>
#include <SFML/Graphics.hpp>
#include "BaseInputHandler.h"

namespace SnakeGame
{
	const int SCREEN_WIDTH = 800;
	const int SCREEN_HEIGHT = 600;	
	const std::u16string GAME_NAME(u"Змейка");
	const std::string RESOURCES_PATH("Resources/");
	const std::string LEVEL_PATH("levels/");

	struct Settings
	{
		std::string selectedLevel{"level1.lvl"};
		float timeOnCell{ 0.5f };
		int tileSize = { 30 };
		float movementSpeed{ (float)tileSize / timeOnCell };
		std::unordered_map<sf::Keyboard::Key, ActionsTypesOnInput> keyMap
		{
			{sf::Keyboard::W, ActionsTypesOnInput::Up},
			{sf::Keyboard::D, ActionsTypesOnInput::Right},
			{sf::Keyboard::S, ActionsTypesOnInput::Down},
			{sf::Keyboard::A, ActionsTypesOnInput::Left},
			{sf::Keyboard::B, ActionsTypesOnInput::Back},
			{sf::Keyboard::P, ActionsTypesOnInput::Pause},
			{sf::Keyboard::Enter, ActionsTypesOnInput::Forward}
		};
	};
};