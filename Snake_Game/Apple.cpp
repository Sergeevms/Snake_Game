#include "Apple.h"
#include "Map.h"
#include "Settings.h"

namespace SnakeGame
{
    AppleFactory::AppleFactory()
    {
        LoadTexture("Apple.png", appleTexture);
    }

    std::shared_ptr<Apple> AppleFactory::GenerateNewApple(const Map * map) const
    {
        return GenerateNewApple(map, map->GetRandomEmptyCell());
    }

    std::shared_ptr<Apple> AppleFactory::GenerateNewApple(const Map * map, const sf::Vector2i position) const
    {
        return std::make_shared<Apple>(position, appleTexture);
    }
}
