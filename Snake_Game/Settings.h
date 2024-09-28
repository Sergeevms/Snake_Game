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

		//General settings
		int screenWidth;
		int screenHeight;
		int tileSize;
		float epsilon;
		float baseTimeOnCell;
		int difficultyLevelCount;
		float timeOnCellDifficultyStep;
		int scoreOnDifficultyStep;
		float timeOnCell;
		int defaultSnakeSize;
		int currentDifficulty;
		int smallRecordsSize;
		int bigRecordsSize;
		float movementSpeed;
		float movingDelayOnStart;
		bool musicOn;
		bool soundOn;
		std::wstring gameName;
		std::string resourcesPath;
		std::string levelPath;
		std::string soundPath;
		std::string fontPath;
		std::string texturePath;
		std::string selectedLevel;
		std::string recordsFileName;
		std::unordered_map<sf::Keyboard::Key, ActionsTypesOnInput> keyMap;
		std::unordered_map<int, float> difficultyToTimeOnCell;
		std::unordered_map<int, int> difficultyToScore;
	};
};