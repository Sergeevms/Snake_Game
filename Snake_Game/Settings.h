#pragma once

namespace SnakeGame
{
	const int SCREEN_WIDTH = 800;
	const int SCEEN_HEIGHT = 600;	
	const std::u16string GAME_NAME(u"Змейка");
	const std::string RESOURCES_PATH("Resources/");
	const std::string LEVEL_PATH("levels/");

	struct Settings
	{
		std::string selectedLevel{"level1.lvl"};
		float timeOnCell{ 3.f };
		int tileSize = { 30 };
		float movementSpeed{ (float)tileSize / timeOnCell };
	};
};