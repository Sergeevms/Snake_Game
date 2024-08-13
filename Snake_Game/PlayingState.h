#pragma once
#include "BaseState.h"
#include "Map.h"
#include "Snake.h"

namespace SnakeGame
{
    class PlayingState :
        public BaseState
    {
    public:
        PlayingState(Settings& settings);
        virtual ~PlayingState() = default;
        virtual void Draw(sf::RenderWindow& window) const override;
        virtual void Update(const float deltaTime) override;
        virtual void HandleInput(std::vector<sf::Event> const& inputEvents) override;
        virtual GameState GetGameState() const override { return GameState::Playing; } ;
    private:
        Map map;
        Snake snake;
    };
}