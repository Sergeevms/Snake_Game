#pragma once
#include "MapObject.h"

namespace SnakeGame
{
    class Map;

    class Apple : public MapObject
    {
    public:
        Apple(sf::Vector2i const& mapCell, sf::Texture const& texture) : MapObject{ mapCell, texture } {};
        virtual MapObjectType GetObjectType() const override { return MapObjectType::Apple; };
    };

    class AppleFactory
    {
    public:
        AppleFactory();
        ~AppleFactory() = default;
        std::shared_ptr<Apple> GenerateNewApple(const Map * map) const;
        std::shared_ptr<Apple> GenerateNewApple(const Map * map, const sf::Vector2i position) const;
    private:
        sf::Texture appleTexture;
        sf::Texture specialAppleTexture;
    };

    class DisorientApple : public Apple
    {
    public:
        DisorientApple(sf::Vector2i const& mapCell, sf::Texture const& texture);
        ~DisorientApple() = default;
    };
}
