#pragma once
#include "BaseMenuInputHandler.h"
#include <unordered_map>


namespace SnakeGame
{
    class PauseMenu;

	class PauseStateInputHandler : public BaseMenuInputHandler
	{
    public:
        PauseStateInputHandler(Game* currentGame, Settings& currentSettings, PauseMenu* currentMenu);
    private:
        void returnToGame();
        void returnToMenu();
	};
}

