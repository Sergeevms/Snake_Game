#pragma once
#include "BaseState.h"
#include "Map.h"
#include "Snake.h"
#include "PlayingInputHandler.h"

namespace SnakeGame
{
    class PlayingState :
        public BaseState
    {
    public:
        PlayingState();
        virtual ~PlayingState() = default;
        virtual void Draw(sf::RenderWindow& window) const override;
        virtual void Update(const float deltaTime) override;
        virtual void HandleInput(const std::vector<sf::Event>& inputEvents) override;
        void resetMovingDelay();
        CollisionResult CheckColition(sf::Vector2i& cell);
    private:
        bool isGameOvered{ false };
        bool sessionStarted{ false };
        int scoreCount{ 0 };
        float delayBeforeMoving;
        float keepSnakeMoveingTime;
        Map map;
        Snake snake;
        PlayingInputHandler inputHandler;        
        sf::Font font;
        sf::Text gameOver;
        sf::Text gameWinned;
        sf::Text scoreText;
    };
}