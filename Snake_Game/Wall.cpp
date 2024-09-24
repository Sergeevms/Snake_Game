#include "Wall.h"

namespace SnakeGame
{
	Wall::Wall(const sf::Vector2i& mapCell, const sf::Texture& texture, const Settings& settings, const Direction direction) : MapObject{ mapCell, texture, settings }
	{		
		sprite.setRotation(directionToRotation.at(direction));
	}
}