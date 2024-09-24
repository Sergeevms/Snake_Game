#pragma once
#include <unordered_map>
#include <SFML/Graphics.hpp>

namespace SnakeGame
{
	enum class ActionsTypesOnInput;

	struct Settings
	{
		Settings();
		void LoadFromFile(const std::string& fileName);
		void SaveToFile(const std::string& fileName);
		void UpdateDifficulty(const int newDiffculty);

		int screenWidth;
		int screenHeight;
		float epsilon;
		float baseTimeOnCell;
		int difficultyLevelCount;
		float timeOnCellDifficultyStep;
		int scoreOnDifficultyStep;
		float timeOnCell;
		int tileSize;
		int defaultSnakeSize;
		int currentDifficulty;
		float movementSpeed;
		float movingDelayOnStart;
		bool musicOn;
		bool soundOn;
		std::u16string gameName;
		std::string resourcesPath;
		std::string levelPath;
		std::string soundPath;
		std::string fontPath;
		std::string texturePath;
		std::string selectedLevel;
		std::unordered_map<sf::Keyboard::Key, ActionsTypesOnInput> keyMap;
		std::unordered_map<int, float> difficultyToTimeOnCell;
		std::unordered_map<int, int> difficultyToScore;
	};
};