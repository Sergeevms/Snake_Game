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
		float movingDelayOnStart;
		int defaultSnakeSize;
		int smallRecordsSize;
		int bigRecordsSize;

		//Difficulty settings
		//Updates difficulty level and set new timeOnCell and movementSpeed according to it
		void UpdateDifficulty(const int newDiffculty);
		int GetCurrentDifficulty() const;
		float GetMovementSpeed() const;
		float GetTimeOnCell() const;
		std::unordered_map<int, float> difficultyToTimeOnCell;
		std::unordered_map<int, int> difficultyToScore;
		int difficultyLevelCount;
		int scoreOnDifficultyStep;
		float baseTimeOnCell;
		float timeOnCellDifficultyStep;
	private:
		int currentDifficulty;
		float movementSpeed;
		float timeOnCell;

	public:

		//Special apples settings
		int spesialAppleSpawnChance;
		bool disorientAppleOn;
		bool goldenAppleOn;
		bool poisionedAppleOn;
		float disorientationTime;
		float goldenAppleLifeTime;
		float goldenAppleScoreModifier;
		//Count of cell before posioned status fades off
		int poisonedCellCount;
		float poisonedSpeedModifire;
		sf::Color disorientAppleColor;
		sf::Color poisionedAppleColor;
		sf::Color goldenAppleColor;
		
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