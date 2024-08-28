#include "Settings.h"

namespace SnakeGame
{
	Settings::Settings()
	{
		for (int i = 0; i < difficultyLevelCount; ++i)
		{
			difficultyToTimeOnCell[i] = baseTimeOnCell - timeOnCellDifficultyStep * i;
			difficultyToScore[i] = scoreOnDifficultyStep * (i + 1) * 1000;
		}
		timeOnCell = difficultyToTimeOnCell[currentDifficulty];
		movementSpeed = (float)tileSize / timeOnCell;
	}
}
