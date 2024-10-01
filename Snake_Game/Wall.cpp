#include "Wall.h"

namespace SnakeGame
{
	Wall::Wall(const sf::Vector2i& mapCell, const sf::Texture& texture, const Direction direction) : MapObject{ mapCell, texture }
	{		
		sprite.setRotation(directionToRotation.at(direction));
	}
}