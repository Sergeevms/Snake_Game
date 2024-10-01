#include "Settings.h"
#include "BaseInputHandler.h"

namespace SnakeGame
{
	Settings* Settings::settings = nullptr;

	Settings::Settings()
	{
		screenWidth = 800;
		screenHeight = 600;
		gameName = L"Змейка";
		resourcesPath = "Resources\\";
		levelPath = resourcesPath + "Levels\\";
		soundPath = resourcesPath + "Sounds\\";
		fontPath = resourcesPath + "Fonts\\";
		texturePath = resourcesPath + "Textures\\";
		epsilon = 1e-7f;
		defaultSnakeSize = 4;
		selectedLevel = "micro.lvl";
		tileSize = 30;
		baseTimeOnCell = 0.75f;
		difficultyLevelCount = 5;		
		scoreOnDifficultyStep = 2;
		timeOnCellDifficultyStep = baseTimeOnCell / (static_cast<float>(difficultyLevelCount + 1));
		for (int i = 0; i < difficultyLevelCount; ++i)
		{
			difficultyToTimeOnCell[i] = baseTimeOnCell - timeOnCellDifficultyStep * i;
			difficultyToScore[i] = scoreOnDifficultyStep * (i + 1);
		}
		UpdateDifficulty(2);
		movementSpeed = static_cast<float>(tileSize) / timeOnCell;
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

		recordsFileName = "Records.dat";
		smallRecordsSize = 5;
		bigRecordsSize = 10;
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
}
