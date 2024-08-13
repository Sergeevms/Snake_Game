#include "Wall.h"

namespace SnakeGame
{
	Wall::Wall(sf::Vector2i const& mapCell, sf::Texture const& texture, Settings const& settings, Direction direction) : MapObject{ mapCell, texture, settings }
	{		
		sprite.setRotation(directionToRotation.at(direction));
	}
}