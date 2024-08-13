#include "MapObject.h"
#include "Utility.h"

namespace SnakeGame
{

	MapObject::MapObject(sf::Vector2i const& mapCell, sf::Texture const& texture, Settings const& settings): 
		sprite(texture), mapCoordinates(mapCell), currentSettings(settings)
	{
		SetOriginByRelative(sprite, relativePositions.at(RelativePosition::Center));
		float tileSize = (float)settings.tileSize;
		SetScaleBySize(sprite, { tileSize, tileSize });
		screenCoordinates.x = tileSize * mapCell.x + tileSize / 2.f;
		screenCoordinates.y = tileSize * mapCell.y + tileSize / 2.f;
		sprite.setPosition(screenCoordinates.x, screenCoordinates.y);
	}

	void MapObject::Draw(sf::RenderWindow& window) const
	{
		window.draw(sprite);
	}

	sf::Vector2i MapObject::GetCellPosition() const
	{
		return mapCoordinates;
	}
}