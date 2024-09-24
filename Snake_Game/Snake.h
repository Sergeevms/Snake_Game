#pragma once
#include <list>
#include "MapObject.h"
#include "Utility.h"

namespace SnakeGame
{

	class SnakeNode: public MapObject
	{
	public:
		SnakeNode(const sf::Vector2i& mapCell, const sf::Texture& texture, const Settings& settings, const Direction direction, const bool isMovingEnabled = true);
		void Update(const float deltaTime);
		void SetDirection(Direction newDirection);
		void SetCellPositionIfMoving(const sf::Vector2i& newCell);
		void UpdateScreenPositionByCell();
		void SetMovingEnabledState(bool isEnabled);
		Direction GetDirection() const;
		virtual MapObjectType GetObjectType() const override { return MapObjectType::Snake; };
	private:
		Direction currentDirection;
		bool isMoving;		
	};

	class PlayingState;
	class Map;
	struct Settings;

	class Snake
	{
	public:
		Snake(const Settings& currentSettings, PlayingState* currentState, Map* currentMap);
		void Update(const float deltaTime);
		void SetNewDirection(Direction direction);
		void Draw(sf::RenderWindow& window) const;
		void LoadFromCharMap(const std::vector<std::string>& charMap, const sf::Vector2i& headPosition);
		void AddNewBody();
	private:
		PlayingState* playingState;
		Map* map;
		std::list<std::shared_ptr<SnakeNode>> nodes;
		Direction newDirection;
		const Settings& settings;
		sf::Texture headTexture;
		sf::Texture bodyTexture;
		float timeTillNextCell{ 0.f };
		bool AddNextBodyFromMap(std::vector<std::vector<bool>>& addedCells, const std::vector<std::string>& charMap, const sf::Vector2i& currentCell);
	};
}