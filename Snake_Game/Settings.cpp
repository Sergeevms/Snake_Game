#include "Settings.h"

namespace SnakeGame
{
	Settings::Settings()
	{
		screenWidth = 800;
		screenHeight = 600;
		gameName = u"Змейка";
		resourcesPath = "Resources\\";
		levelPath = resourcesPath + "Levels\\";
		soundPath = resourcesPath + "Sounds\\";
		fontPath = resourcesPath + "Fonts\\";
		texturePath = resourcesPath + "Textures\\";
		epsilon = 1e-7f;
		baseTimeOnCell = 0.75f;
		difficultyLevelCount = 5;
		timeOnCellDifficultyStep = baseTimeOnCell / static_cast<float>(difficultyLevelCount + 1);
		scoreOnDifficultyStep = 2;
		selectedLevel = "level1.lvl";
		tileSize = 30;
		currentDifficulty = 4;
		movementSpeed = static_cast<float>(tileSize) / timeOnCell;
		movingDelayOnStart = 3.f;
		for (int i = 0; i < difficultyLevelCount; ++i)
		{
			difficultyToTimeOnCell[i] = baseTimeOnCell - timeOnCellDifficultyStep * i;
			difficultyToScore[i] = scoreOnDifficultyStep * (i + 1) * 1000;
		}
		timeOnCell = difficultyToTimeOnCell[currentDifficulty];
		movementSpeed = (float)tileSize / timeOnCell;
		musicOn = true;
		soundOn = true;
		keyMap[sf::Keyboard::W] = ActionsTypesOnInput::Up;
		keyMap[sf::Keyboard::D] = ActionsTypesOnInput::Right;
		keyMap[sf::Keyboard::S] = ActionsTypesOnInput::Down;
		keyMap[sf::Keyboard::A] = ActionsTypesOnInput::Left;
		keyMap[sf::Keyboard::B] = ActionsTypesOnInput::Back;
		keyMap[sf::Keyboard::P] = ActionsTypesOnInput::Pause;
		keyMap[sf::Keyboard::Enter] = ActionsTypesOnInput::Forward;
	}

	void Settings::LoadFromFile(const std::string& fileName)
	{

	}

	void Settings::SaveToFile(const std::string& fileName)
	{

	}
}
