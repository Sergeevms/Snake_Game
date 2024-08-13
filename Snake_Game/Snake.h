#pragma once
#include <list>
#include "MapObject.h"
#include "Utility.h"
#include "Settings.h"

namespace SnakeGame
{

	class SnakeNode: public MapObject
	{
	public:
		SnakeNode(sf::Vector2i const& mapCell, sf::Texture const& texture, Settings const& settings, Direction direction, const float timeTillMove = 0.f);
		void Update(const float deltaTime);
		void setDirection(Direction newDirection);
		Direction GetDirection() const;
		virtual MapObjectType GetObjectType() const override { return MapObjectType::Snake; };
	private:
		Direction currentDirection;
		float timeTillMovingAvaliable;
	};

	class Snake
	{
	public:
		Snake(Settings const& settings);
		void Update(const float deltaTime);
		void SetNewDirection(Direction direction);
		void Draw(sf::RenderWindow& window) const;
		void LoadFromCharMap(std::vector <std::string> const& charMap, sf::Vector2i const& headPosition);
	private:
		std::list<std::shared_ptr<SnakeNode>> nodes;
		Direction newDirection;
		Settings const& currentSettings;
		sf::Texture headTexture;
		sf::Texture bodyTexture;
		float timeTillNextCell;
		bool AddNextBody(std::vector<std::vector<bool>>& addedCells, std::vector<std::string> const& charMap, sf::Vector2i const& currentCell);
	};
}