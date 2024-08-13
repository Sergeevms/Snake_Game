#pragma once
#include "MapObject.h"

namespace SnakeGame
{
    class Apple :
        public MapObject
    {
    public:
        Apple(sf::Vector2i const& mapCell, sf::Texture const& texture, Settings const& settings) : MapObject{ mapCell, texture, settings } {};
        virtual MapObjectType GetObjectType() const override { return MapObjectType::Apple; } ;
    };
}
