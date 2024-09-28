#pragma once
#include <vector>
#include <unordered_map>
#include <SFML/Graphics.hpp>

#include "BaseMenuInputHandler.h"

namespace SnakeGame
{
    class MainMenu;
    
    class MainMenuInputHandler : public BaseMenuInputHandler
    {
    public:
        MainMenuInputHandler(Game* currentGame, Settings & currentSettings, MainMenu* currentMenu);
        void ExitGame();
        void StartPlaying();
        void SwitchMusic();
        void SwitchSound();
        void SwitchDifficulty();
    private:
        MainMenu* menu;
    };
}

