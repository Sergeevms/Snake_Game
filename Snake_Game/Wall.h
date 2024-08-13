#pragma once
#include "MapObject.h"
#include "Utility.h"

namespace SnakeGame
{
    class Wall :
        public MapObject
    {
    public:
        Wall(sf::Vector2i const& mapCell, sf::Texture const& texture, Settings const& settings, Direction direction);
        virtual MapObjectType GetObjectType() const override { return MapObjectType::Wall; };
    };
}