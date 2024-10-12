#pragma once
#include <unordered_map>
#include <SFML/Graphics.hpp>

namespace SnakeGame
{
	enum class ActionsTypesOnInput;

	struct Settings
	{
		static Settings* GetSettings()
		{
			if (settings == nullptr)
			{
				settings = new Settings();
			}
			return settings;
		};

		void LoadFromFile(const std::string& fileName);
		void SaveToFile(const std::string& fileName);
		void UpdateDifficulty(const int newDiffculty);
		sf::Vector2f ScreenCenter();
		sf::Vector2f ScreenSize();

		//General settings
		int screenWidth;
		int screenHeight;
		int tileSize;
		std::wstring gameName;
		std::wstring defaultPlayerName;
		float epsilon;
		float popUpSpacing;
		float popUpBorder;
		int defaultSnakeSize;
		int smallRecordsSize;
		int bigRecordsSize;

		//Difficulty settings

		std::unordered_map<int, float> difficultyToTimeOnCell;
		std::unordered_map<int, int> difficultyToScore;
		int difficultyLevelCount;
		int currentDifficulty;
		int scoreOnDifficultyStep;
		float movementSpeed;
		float movingDelayOnStart;
		float baseTimeOnCell;
		float timeOnCellDifficultyStep;
		float timeOnCell;

		//Special apples settings
		int SpesialAppleSpawnChance;
		bool DisorientAppleOn;
		bool GoldenAppleOn;
		bool PoisionedAppleOn;
		float DisorientationTime;
		float GoldenAppleLifeTime;
		float PoisnedTime;
		float PoisnedSpeedModifire;

		//Sound settings

		bool musicOn;
		bool soundOn;		
				
		//Paths to files

		std::string resourcesPath;
		std::string levelPath;
		std::string soundPath;
		std::string fontPath;
		std::string texturePath;


		std::string selectedLevel;
		std::string recordsFileName;
		
		//Control settings
		std::unordered_map<sf::Keyboard::Key, ActionsTypesOnInput> keyMap;
	private:
		Settings();
		static Settings* settings;
	};
};