#include "Apple.h"
#include "Map.h"
#include "Settings.h"

namespace SnakeGame
{
    AppleFactory::AppleFactory()
    {
        LoadTexture("Apple.png", appleTexture);
        LoadTexture("AppleSpecial.png", specialAppleTexture);
    }

    std::shared_ptr<Apple> AppleFactory::GenerateNewApple(const Map * map) const
    {
        return GenerateNewApple(map, map->GetRandomEmptyCell());
    }

    std::shared_ptr<Apple> AppleFactory::GenerateNewApple(const Map * map, const sf::Vector2i position) const
    {
        int roll = rand() % 100;
        if (roll < Settings::GetSettings()->SpesialAppleSpawnChance)
        {
            return std::make_shared<DisorientApple>(position, specialAppleTexture);
        }
        else
        {
            return std::make_shared<Apple>(position, appleTexture);
        }
    }

    DisorientApple::DisorientApple(sf::Vector2i const& mapCell, sf::Texture const& texture) : Apple(mapCell, texture)
    {        
        sprite.setColor(Settings::GetSettings()->DisorientAppleColor);
    }
}
