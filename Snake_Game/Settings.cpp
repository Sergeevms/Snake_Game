#include "Settings.h"
#include "BaseInputHandler.h"
#include "Utility.h"

namespace SnakeGame
{
	Settings* Settings::settings = nullptr;

	Settings::Settings()
	{
		screenWidth = 800;
		screenHeight = 600;
		gameName = L"������";
		defaultPlayerName = L"XYZ";
		epsilon = 1e-7f;
		defaultSnakeSize = 4;
		selectedLevel = "level1.lvl";
		tileSize = 30;
		baseTimeOnCell = 0.75f;
		difficultyLevelCount = 5;		
		scoreOnDifficultyStep = 2;
		popUpSpacing = 100.f;
		popUpBorder = 5.f;
		timeOnCellDifficultyStep = baseTimeOnCell / (static_cast<float>(difficultyLevelCount + 1));

		for (int i = 0; i < difficultyLevelCount; ++i)
		{
			difficultyToTimeOnCell[i] = baseTimeOnCell - timeOnCellDifficultyStep * i;
			difficultyToScore[i] = scoreOnDifficultyStep * (i + 1);
		}
		
		UpdateDifficulty(3);

		specialAppleSpawnChance = 75;
		disorientAppleOn = true;
		goldenAppleOn = true;
		poisionedAppleOn = true;
		disorientationTime = 10.f;
		goldenAppleLifeTime = 10.f;
		goldenAppleScoreModifier = 1.5f;
		poisonedCellCount = 50;
		poisonedSpeedModifire = 1.5f;
		disorientAppleColor = sf::Color(219, 143, 255, 255);
		poisionedAppleColor = sf::Color(146, 255, 204, 255);
		goldenAppleColor = sf::Color(235, 189, 43, 255);

		movingDelayOnStart = 3.f;

		musicOn = true;
		soundOn = true;

		randomWallsOn = true;
		randomWallCoefficient = 0.15f;

		keyMap[sf::Keyboard::W] = ActionsTypesOnInput::Up;
		keyMap[sf::Keyboard::D] = ActionsTypesOnInput::Right;
		keyMap[sf::Keyboard::S] = ActionsTypesOnInput::Down;
		keyMap[sf::Keyboard::A] = ActionsTypesOnInput::Left;
		keyMap[sf::Keyboard::B] = ActionsTypesOnInput::Back;
		keyMap[sf::Keyboard::P] = ActionsTypesOnInput::Pause;
		keyMap[sf::Keyboard::Enter] = ActionsTypesOnInput::Forward;
		keyMap[sf::Keyboard::BackSpace] = ActionsTypesOnInput::BackSpace;

		recordsFileName = "Records.dat";
		smallRecordsSize = 5;
		bigRecordsSize = 10;

		resourcesPath = "Resources\\";
		levelPath = resourcesPath + "Levels\\";
		soundPath = resourcesPath + "Sounds\\";
		fontPath = resourcesPath + "Fonts\\";
		texturePath = resourcesPath + "Textures\\";
	}

	void Settings::LoadFromFile(const std::string& fileName)
	{

	}

	void Settings::SaveToFile(const std::string& fileName)
	{

	}

	void Settings::UpdateDifficulty(const int newDiffculty)
	{
		currentDifficulty = newDiffculty;
		timeOnCell = difficultyToTimeOnCell[currentDifficulty];
		movementSpeed = static_cast<float>(tileSize) / timeOnCell;
	}

	int Settings::GetCurrentDifficulty() const
	{
		return currentDifficulty;
	}

	float Settings::GetMovementSpeed() const
	{
		return movementSpeed;
	}

	float Settings::GetTimeOnCell() const
	{
		return timeOnCell;
	}

	sf::Vector2f Settings::ScreenCenter()
	{
		return ScreenSize() * 0.5f;
	}

	sf::Vector2f Settings::ScreenSize()
	{
		return sf::Vector2f({static_cast<float>(screenWidth), static_cast<float>(screenHeight)});
	}
}
