#pragma once
#include "MapObject.h"
#include "Utility.h"

namespace SnakeGame
{

    struct Settings;

    class Wall :
        public MapObject
    {
    public:
        Wall(const sf::Vector2i& mapCell, const sf::Texture& texture, const Direction direction);
        virtual MapObjectType GetObjectType() const override { return MapObjectType::Wall; };
    };
}