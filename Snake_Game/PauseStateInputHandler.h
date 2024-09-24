#pragma once
#include "BaseInputHandler.h"
#include <unordered_map>


namespace SnakeGame
{
    class PauseStateInputHandler;
    typedef void (PauseStateInputHandler::* InputReaction)();

    class PauseMenu;
    enum class ActivateReactionPauseMenu;

	class PauseStateInputHandler : public BaseInputHandler
	{
    public:
        PauseStateInputHandler(Game* currentGame, Settings& currentSettings, PauseMenu* currentMenu);
        void HandleInputEvents(const std::vector<sf::Event>& input) override;
    private:
        PauseMenu* menu;
        std::unordered_map<ActionsTypesOnInput, InputReaction> actionMapping;
        std::unordered_map<ActivateReactionPauseMenu, InputReaction> activateMapping;

        void selectNext();
        void selectPrevious();
        void activateCurrent();
        void returnToGame();
        void returnToMenu();
	};
}

