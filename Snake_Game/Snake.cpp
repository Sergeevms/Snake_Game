#include "Snake.h"
#include "Settings.h"
#include "PlayingState.h"

namespace SnakeGame
{

	SnakeNode::SnakeNode(const sf::Vector2i& mapCell, const sf::Texture& texture, const Direction direction, const bool isMovingEnabled) :
		MapObject(mapCell, texture), currentDirection(direction), isMoving(isMovingEnabled)
	{

	}

	void SnakeNode::Update(const float deltaTime)
	{
		if (isMoving)
		{
			const float movementDistance = deltaTime * Settings::GetSettings()->movementSpeed;
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

	void SnakeNode::SetCellPositionIfMoving(const sf::Vector2i& newCell)
	{
		if (isMoving)
		{
			mapCoordinates.x = newCell.x;
			mapCoordinates.y = newCell.y;
		}
	}

	void SnakeNode::UpdateScreenPositionByCell()
	{
		Settings* settings = Settings::GetSettings();
		screenCoordinates.x = settings->tileSize * mapCoordinates.x + settings->tileSize / 2.f;
		screenCoordinates.y = settings->tileSize * mapCoordinates.y + settings->tileSize / 2.f;
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

	Snake::Snake(PlayingState* currentState, Map* currentMap): playingState(currentState),
		newDirection(Direction::None), map(currentMap)
	{
		Settings* settings = Settings::GetSettings();
		LoadTexture("SnakeHead.png", headTexture);
		LoadTexture("SnakeBody.png", bodyTexture);
	}

	void Snake::Update(const float deltaTime)
	{		
		timeTillNextCell -= deltaTime;
		Settings* settings = Settings::GetSettings();

		for (auto& node : nodes)
		{
			node.get()->SetColor(sf::Color::White);
		}

		//handle special states
		if (timeTillDisorientedFallse > settings->epsilon)
		{
			timeTillDisorientedFallse -= deltaTime;
			for (auto& node : nodes)
			{
				node.get()->SetColor(settings->DisorientAppleColor);
			}
		}

		if (timeTillNextCell > settings->epsilon)
		{
			for (auto& node : nodes)
			{
				node->Update(deltaTime);
			}
		}
		else
		{
			timeTillNextCell = settings->timeOnCell;
			nodes.back()->SetMovingEnabledState(true);
			std::shared_ptr<SnakeNode> head = nodes.front();
			sf::Vector2i cellToCheck{ head->GetCellPosition().x + static_cast<int>(directionVectors.at(newDirection).x),
				head->GetCellPosition().y + static_cast<int>(directionVectors.at(newDirection).y) };
			if (playingState->CheckColition(cellToCheck))
			{
				Direction nextNodeDirection = newDirection;
				for (auto node = nodes.begin(); node != nodes.end(); ++node)
				{
					map->RemoveMapObject((*node));
					sf::Vector2i currentCell = (*node)->GetCellPosition();
					Direction currentDirection = (*node)->GetDirection();
					(*node)->UpdateScreenPositionByCell();
					(*node)->SetCellPositionIfMoving({ currentCell.x + static_cast<int>(directionVectors.at(nextNodeDirection).x),
						currentCell.y + static_cast<int>(directionVectors.at(nextNodeDirection).y) });
					(*node)->SetDirection(nextNodeDirection);
					nextNodeDirection = currentDirection;
					map->EmplaceMapObject((*node));
					(*node)->Update(deltaTime);
				}
			}
			else
			{
				head->SetDirection(newDirection);
			}
		}
	}

	void Snake::SetNewDirection(Direction direction)
	{
		Direction possibleDirection = timeTillDisorientedFallse > Settings::GetSettings()->epsilon ? OpossiteDirection(direction) : direction;
		if (possibleDirection != OpossiteDirection(nodes.front()->GetDirection()))
		{
			newDirection = possibleDirection;
		}
	}

	void Snake::Draw(sf::RenderWindow& window) const
	{
		for (auto node = nodes.rbegin(); node != nodes.rend(); ++node)
		{
			(*node)->Draw(window);
		}
	}

	void Snake::LoadFromCharMap(const std::vector<std::string>& charMap, const sf::Vector2i& headPosition)
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
		nodes.push_back(std::make_shared<SnakeNode>(currentCell, headTexture, Direction::None));
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
		for (auto& node : nodes)
		{
			map->EmplaceMapObject((node));
		}
	}

	void Snake::AddNewBody()
	{
		std::shared_ptr<SnakeNode> lastNode = nodes.back();
		nodes.push_back(std::make_shared<SnakeNode>(lastNode->GetCellPosition(), bodyTexture, lastNode->GetDirection(), false));
	}

	void Snake::GetDisoriented()
	{
		timeTillDisorientedFallse = Settings::GetSettings()->DisorientationTime;
	}

	bool Snake::AddNextBodyFromMap(std::vector<std::vector<bool>>& addedCells, const std::vector<std::string>& charMap, const sf::Vector2i& currentCell)
	{
		for (auto& curDir : directionVectors)
		{
			sf::Vector2i checkingCell{ currentCell.x + static_cast<int>(curDir.second.x), currentCell.y + static_cast<int>(curDir.second.y) };

			if (InRightOpenInterval(0, static_cast<int>(charMap.size()), checkingCell.y) &&
				InRightOpenInterval(0, static_cast<int>(charMap.at(checkingCell.y).size()), checkingCell.x) &&
				charMap[checkingCell.y][checkingCell.x] == 'B' &&
				addedCells[checkingCell.y][checkingCell.x] == false)
			{				
				nodes.push_back(std::make_shared<SnakeNode>(checkingCell, bodyTexture, OpossiteDirection(curDir.first)));
				addedCells[checkingCell.y][checkingCell.x] = true;
				return true;
			}
		}
		return false;
	}
}