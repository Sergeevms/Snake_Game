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
        void resetMovingDelay();
        //virtual GameState GetGameState() const override { return GameState::Playing; } ;
        CollisionResult CheckColition(sf::Vector2i& cell);
    private:
        bool isGameOvered{ false };
        bool sessionStarted{ false };
        int scoreCount{ 0 };
        float delayBeforeMoving;
        Map map;
        Snake snake;
        PlayingInputHandler inputHandler;        
        sf::Font font;
        sf::Text gameOver;
        sf::Text scoreText;
        DebugGrid debugGrid;
    };
}