#pragma once
#include <SFML/Graphics.hpp>
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

	enum class CollisionResult
	{
		None,
		GameOver,
		AppleEaten
	};

	const std::unordered_map<MapObjectType, CollisionResult> collitionResults
	{
		{MapObjectType::None, CollisionResult::None},
		{MapObjectType::Wall, CollisionResult::GameOver},
		{MapObjectType::Apple, CollisionResult::AppleEaten},
		{MapObjectType::Snake, CollisionResult::GameOver}
	};

	const std::unordered_map<Direction, float> directionToRotation
	{ 
		{Direction::Up, 0.f}, 
		{Direction::Rigth, 90.f},
		{Direction::Down, 180.f},
		{Direction::Left, 270.f} 
	};

	struct Settings;

	class MapObject
	{
	public:
		MapObject(const sf::Vector2i& mapCell, const sf::Texture& texture, const Settings& settings);
		virtual ~MapObject() = default;
		virtual MapObjectType GetObjectType() const = 0;
		virtual void Draw(sf::RenderWindow&) const;
		sf::Vector2i GetCellPosition() const;
	protected:
		sf::Vector2i mapCoordinates;
		sf::Vector2f screenCoordinates;
		sf::Sprite sprite;
		const Settings& currentSettings;
	};
}