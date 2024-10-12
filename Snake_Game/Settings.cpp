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
		gameName = L"Змейка";
		defaultPlayerName = L"XYZ";
		epsilon = 1e-7f;
		defaultSnakeSize = 4;
		selectedLevel = "micro.lvl";
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
		movementSpeed = static_cast<float>(tileSize) / timeOnCell;

		SpesialAppleSpawnChance = 75;
		DisorientAppleOn = true;
		GoldenAppleOn = false;
		PoisionedAppleOn = false;
		DisorientationTime = 10.f;
		GoldenAppleLifeTime = 10.f;
		PoisnedTime = 10.f;
		PoisnedSpeedModifire = 1.5f;

		movingDelayOnStart = 3.f;

		musicOn = true;
		soundOn = true;

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
		movementSpeed = (float)tileSize / timeOnCell;
	}

	sf::Vector2f Settings::ScreenCenter()
	{
		return sf::Vector2f(multiplyVectorByScalar(ScreenSize(), 0.5f));
	}

	sf::Vector2f Settings::ScreenSize()
	{
		return sf::Vector2f({static_cast<float>(screenWidth), static_cast<float>(screenHeight)});
	}
}
