#include <assert.h>
#include "Utility.h"
#include "Settings.h"

namespace SnakeGame
{
    sf::Vector2f multiplyVectorByScalar(sf::Vector2f const& vector, float scalar)
    {
        return sf::Vector2f(vector.x * scalar, vector.y * scalar);
    }

    Direction SnakeGame::OpossiteDirection(Direction direction)
    {
        switch (direction)
        {
        case Direction::Left:
        {
            return Direction::Rigth;
            break;
        }
        case Direction::Rigth:
        {
            return Direction::Left;
            break;
        }
        case Direction::Up:
        {
            return Direction::Down;
            break;
        }
        case Direction::Down:
        {
            return Direction::Up;
            break;
        }
        default:
            return Direction::None;
        }        
    }

    void LoadTexture(std::string const& fileName, sf::Texture& texture)
    {
#ifndef NDEBUG
        assert(texture.loadFromFile(fileName));
#else 
        texture.loadFromFile(fileName);
#endif
    }

    sf::Vector2f RelativePositionByOrientationAndAlignment(const Orientation orientation, const Alignment alignment)
    {
        RelativePosition relativeOrigin;
        switch (alignment)
        {
        case Alignment::Min:
        {
            relativeOrigin = RelativePosition::TopLeft;
            break;
        }
        case Alignment::Middle:
        {
            relativeOrigin = orientation == Orientation::Vertical ? RelativePosition::TopMiddle : RelativePosition::MiddleLeft;
            break;
        }
        case Alignment::Max:
        {
            relativeOrigin = orientation == Orientation::Vertical ? RelativePosition::TopRight : RelativePosition::BottomLeft;
            break;
        }
        }
        return relativePositions.at(relativeOrigin);
    }
}