#pragma once
#include <SFML/Graphics.hpp>
#include "Settings.h"
#include "Utility.h"

namespace SnakeGame
{
	enum class MapObjectType
	{
		None,
		Wall,
		Apple,
		Snake
	};

	const std::unordered_map<Direction, float> directionToRotation
	{ 
		{Direction::Up, 0.f}, 
		{Direction::Rigth, 90.f},
		{Direction::Down, 180.f},
		{Direction::Left, 270.f} };

	class MapObject
	{
	public:
		MapObject(sf::Vector2i const& mapCell, sf::Texture const& texture, Settings const& settings);
		virtual ~MapObject() = default;
		virtual MapObjectType GetObjectType() const = 0;
		virtual void Draw(sf::RenderWindow&) const;
		sf::Vector2i GetCellPosition() const;
	protected:
		sf::Vector2i mapCoordinates;
		sf::Vector2f screenCoordinates;
		sf::Sprite sprite;
		Settings const& currentSettings;
	};
}