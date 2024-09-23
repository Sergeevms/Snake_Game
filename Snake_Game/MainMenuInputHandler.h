#pragma once
#include <vector>
#include <unordered_map>
#include <SFML/Graphics.hpp>

#include "BaseInputHandler.h"

namespace SnakeGame
{
    class MainMenuInputHandler;
    typedef void (MainMenuInputHandler::* InputReaction)();

    class MainMenu;
    enum class ActivateReactionMainMenu;

    class MainMenuInputHandler : public BaseInputHandler
    {
    public:
        MainMenuInputHandler(Game* currentGame, Settings & currentSettings, MainMenu* currentMenu);
        void HandleInputEvents(std::vector<sf::Event> const& input) override;
    private:
        MainMenu* menu;
        std::unordered_map<ActionsTypesOnInput, InputReaction> actionMapping;
        std::unordered_map<ActivateReactionMainMenu, InputReaction> activateMapping;
        void SelectNext();
        void SelectPrevious();
        void ActivateCurrent();
        void GoBack();
        void ExitGame();
        void StartPlaying();
        void SwitchMusic();
        void SwitchSound();
    };
}

