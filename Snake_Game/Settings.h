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

	const float EPSILON = 1e-7f;
	const float baseTimeOnCell = 0.75f;
	const int difficultyLevelCount = 5;
	const float timeOnCellDifficultyStep = baseTimeOnCell / (float(difficultyLevelCount + 1));
	const int scoreOnDifficultyStep = 2;
	

	struct Settings
	{
		Settings();
		std::string selectedLevel{"level1.lvl"};
		float timeOnCell{ baseTimeOnCell };
		int tileSize { 30 };
		int currentDifficulty = 4;
		float movementSpeed{ (float)tileSize / timeOnCell };
		float movingDelayOnStart {3.f};
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
		std::unordered_map<int, float> difficultyToTimeOnCell;
		std::unordered_map<int, int> difficultyToScore;
	};
};