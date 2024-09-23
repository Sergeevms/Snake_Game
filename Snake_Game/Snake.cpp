#include "Snake.h"
#include "Settings.h"
#include "PlayingState.h"

namespace SnakeGame
{

	SnakeNode::SnakeNode(sf::Vector2i const& mapCell, sf::Texture const& texture, Settings const& settings, Direction direction, const bool isMovingEnabled) :
		MapObject(mapCell, texture, settings), currentDirection(direction), isMoving(isMovingEnabled)
	{

	}

	void SnakeNode::Update(const float deltaTime)
	{
		if (isMoving)
		{
			const float movementDistance = deltaTime * currentSettings.movementSpeed;
			sf::Vector2f movement = multiplyVectorByScalar(directionVectors.at(currentDirection), movementDistance);
			screenCoordinates.x += movement.x;
			screenCoordinates.y += movement.y;
			sprite.setPosition(screenCoordinates.x, screenCoordinates.y);
		}
	}

	void SnakeNode::SetDirection(Direction newDirection)
	{
		currentDirection = newDirection;
		sprite.setRotation(directionToRotation.at(currentDirection));
	}

	void SnakeNode::SetCellPositionIfMoving(sf::Vector2i const& newCell)
	{
		if (isMoving)
		{
			mapCoordinates.x = newCell.x;
			mapCoordinates.y = newCell.y;
		}
	}

	void SnakeNode::UpdateScreenPositionByCell()
	{
		screenCoordinates.x = currentSettings.tileSize * mapCoordinates.x + currentSettings.tileSize / 2.f;
		screenCoordinates.y = currentSettings.tileSize * mapCoordinates.y + currentSettings.tileSize / 2.f;
		sprite.setPosition(screenCoordinates.x, screenCoordinates.y);
	}

	void SnakeNode::SetMovingEnabledState(bool isEnabled)
	{
		isMoving = isEnabled;
	}

	Direction SnakeNode::GetDirection() const
	{
		return currentDirection;
	}

	Snake::Snake(Settings const& currentSettings, PlayingState* currentState, Map* currentMap): settings(currentSettings), playingState(currentState),
		newDirection(Direction::None), map(currentMap)
	{
		LoadTexture(settings.texturePath + "SnakeHead.png", headTexture);
		LoadTexture(settings.texturePath + "SnakeBody.png", bodyTexture);
	}

	void Snake::Update(const float deltaTime)
	{		
		timeTillNextCell -= deltaTime;
		if (timeTillNextCell > settings.epsilon)
		{
			for (auto& node : nodes)
			{
				node->Update(deltaTime);
			}
		}
		else
		{
			timeTillNextCell = settings.timeOnCell;
			nodes.back()->SetMovingEnabledState(true);
			std::shared_ptr<SnakeNode> head = nodes.front();
			sf::Vector2i cellToCheck{ head->GetCellPosition().x + (int)directionVectors.at(newDirection).x,
				head->GetCellPosition().y + (int)directionVectors.at(newDirection).y };
			if (playingState->CheckColition(cellToCheck) != CollisionResult::GameOver)
			{
				Direction nextNodeDirection = newDirection;
				for (auto node = nodes.begin(); node != nodes.end(); ++node)
				{
					map->RemoveMapObject((*node));
					sf::Vector2i currentCell = (*node)->GetCellPosition();
					Direction currentDirection = (*node)->GetDirection();
					(*node)->UpdateScreenPositionByCell();
					(*node)->SetCellPositionIfMoving({ currentCell.x + (int)directionVectors.at(nextNodeDirection).x, currentCell.y + (int)directionVectors.at(nextNodeDirection).y });
					(*node)->SetDirection(nextNodeDirection);
					nextNodeDirection = currentDirection;
					map->EmplaceMapObject((*node));
					(*node)->Update(deltaTime);
				}
			}
		}
	}

	void Snake::SetNewDirection(Direction direction)
	{
		if (direction != OpossiteDirection(nodes.front()->GetDirection()))
		{
			newDirection = direction;
		}
	}

	void Snake::Draw(sf::RenderWindow& window) const
	{
		for (auto node = nodes.rbegin(); node != nodes.rend(); ++node)
		{
			(*node)->Draw(window);
		}
	}

	void Snake::LoadFromCharMap(std::vector<std::string> const& charMap, sf::Vector2i const& headPosition)
	{
		nodes.clear();
		sf::Vector2i currentCell = headPosition;
		std::vector<std::vector<bool>> addedToSnake;
		addedToSnake.reserve(charMap.size());
		for (auto& row : charMap)
		{
			addedToSnake.push_back(std::vector<bool>(row.size(), false));
		}
		addedToSnake[currentCell.y][currentCell.x] = true;
		nodes.push_back(std::make_shared<SnakeNode>(currentCell, headTexture, settings, Direction::None));
		while (AddNextBodyFromMap(addedToSnake, charMap, currentCell))
		{
			currentCell = nodes.back()->GetCellPosition();
		}
		Direction possibleDirection = ((++nodes.begin())->get())->GetDirection();
		if (charMap[headPosition.y + static_cast<int>(directionVectors.at(possibleDirection).y)][headPosition.x + static_cast<int>(directionVectors.at(possibleDirection).x)] == 'E' ||
			charMap[headPosition.y + static_cast<int>(directionVectors.at(possibleDirection).y)][headPosition.x + static_cast<int>(directionVectors.at(possibleDirection).x)] == 'A')
		{
			nodes.front()->SetDirection(possibleDirection);
			newDirection = possibleDirection;
		}
		else
		{
			for (auto& curDir : directionVectors)
			{
				if (charMap[headPosition.y + static_cast<int>(curDir.second.y)][headPosition.x + static_cast<int>(curDir.second.x)] == 'E' ||
					charMap[headPosition.y + static_cast<int>(curDir.second.y)][headPosition.x + static_cast<int>(curDir.second.x)] == 'A')
				{
					nodes.front()->SetDirection(curDir.first);
					newDirection = curDir.first;
				}
			}
		}
	}

	void Snake::AddNewBody()
	{
		std::shared_ptr<SnakeNode> lastNode = nodes.back();
		nodes.push_back(std::make_shared<SnakeNode>(lastNode->GetCellPosition(), bodyTexture, settings, lastNode->GetDirection(), false));
	}

	std::list<std::shared_ptr<SnakeNode>> const& Snake::GetNodes() const
	{
		return nodes;
	}

	bool Snake::AddNextBodyFromMap(std::vector<std::vector<bool>>& addedCells, std::vector<std::string> const& charMap, sf::Vector2i const& currentCell)
	{
		for (auto& curDir : directionVectors)
		{
			sf::Vector2i checkingCell{ currentCell.x + (int)curDir.second.x, currentCell.y + (int)curDir.second.y };

			if (InRightOpenInterval(0, (int)charMap.size(), checkingCell.y) &&
				InRightOpenInterval(0, (int)charMap.at(checkingCell.y).size(), checkingCell.x) &&
				charMap[checkingCell.y][checkingCell.x] == 'B' &&
				addedCells[checkingCell.y][checkingCell.x] == false)
			{				
				nodes.push_back(std::make_shared<SnakeNode>(checkingCell, bodyTexture, settings, OpossiteDirection(curDir.first)));
				addedCells[checkingCell.y][checkingCell.x] = true;
				return true;
			}
		}
		return false;
	}
}