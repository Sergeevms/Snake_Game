#include "MapObject.h"
#include "Settings.h"

namespace SnakeGame
{

	MapObject::MapObject(const sf::Vector2i& mapCell, const sf::Texture& texture): 
		sprite(texture), mapCoordinates(mapCell)
	{
		SetOriginByRelative(sprite, relativePositions.at(RelativePosition::Center));

		float tileSize = static_cast<float>(Settings::GetSettings()->tileSize);
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