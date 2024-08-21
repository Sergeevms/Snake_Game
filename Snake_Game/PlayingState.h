#pragma once
#include "BaseState.h"
#include "Map.h"
#include "Snake.h"
#include "PlayingInputHandler.h"
#include "DebugGrid.h"

namespace SnakeGame
{
    class PlayingState :
        public BaseState
    {
    public:
        PlayingState(Game* game, Settings& settings);
        virtual ~PlayingState() = default;
        virtual void Draw(sf::RenderWindow& window) const override;
        virtual void Update(const float deltaTime) override;
        virtual void HandleInput(std::vector<sf::Event> const& inputEvents) override;
        virtual GameState GetGameState() const override { return GameState::Playing; } ;
        void CheckColition(sf::Vector2i& cell);
    private:
        bool isGameOvered{ false };
        Map map;
        Snake snake;
        PlayingInputHandler inputHandler;
        sf::Font font;
        sf::Text gameOver;
        DebugGrid debugGrid;
    };
}