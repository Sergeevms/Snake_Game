#include "Snake.h"
#include "Settings.h"
#include "PlayingState.h"

namespace SnakeGame
{

	SnakeNode::SnakeNode(const sf::Vector2i& mapCell, const sf::Texture& texture, const Direction direction, const bool isMovingEnabled) :
		MapObject(mapCell, texture), currentDirection(direction), isMoving(isMovingEnabled)
	{

	}

	void SnakeNode::Update(const float deltaTime, const float speedModifire = 1.f)
	{
		if (isMoving)
		{
			const float movementDistance = deltaTime * Settings::GetSettings()->GetMovementSpeed() * speedModifire;
			sf::Vector2f movement = directionVectorsF.at(currentDirection) * movementDistance;
			screenCoordinates += movement;
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
		sf::Vector2f mapCellF(mapCoordinates);
		screenCoordinates = (mapCellF + relativePositions.at(RelativePosition::Center)) * settings->tileSize;
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

		sf::Color snakeColor = sf::Color::White;

		//handle special states
		if (timeTillDisorientedFall > 0.f)
		{
			timeTillDisorientedFall -= deltaTime;
			snakeColor *= settings->disorientAppleColor;
		}

		if (timeTillPoisonedFall > 0.f)
		{
			timeTillPoisonedFall -= deltaTime;
			snakeColor *= settings->poisionedAppleColor;
		}

		for (auto& node : nodes)
		{
			node.get()->SetColor(snakeColor);
		}

		if (timeTillNextCell > 0.f)
		{
			for (auto& node : nodes)
			{
				node->Update(deltaTime, timeTillPoisonedFall > 0.f ? settings->poisonedSpeedModifire : 1.f);
			}
		}
		else
		{
			timeTillNextCell = settings->GetTimeOnCell() / (timeTillPoisonedFall > 0.f ? settings->poisonedSpeedModifire : 1.f);
			nodes.back()->SetMovingEnabledState(true);
			std::shared_ptr<SnakeNode> head = nodes.front();
			sf::Vector2i cellToCheck = head->GetCellPosition() + directionVectorsI.at(newDirection);
			if (playingState->CheckColition(cellToCheck))
			{
				Direction nextNodeDirection = newDirection;
				for (auto node = nodes.begin(); node != nodes.end(); ++node)
				{
					map->RemoveMapObject((*node));
					sf::Vector2i currentCell = (*node)->GetCellPosition();
					Direction currentDirection = (*node)->GetDirection();
					(*node)->UpdateScreenPositionByCell();
					(*node)->SetCellPositionIfMoving(currentCell + directionVectorsI.at(nextNodeDirection));
					(*node)->SetDirection(nextNodeDirection);
					nextNodeDirection = currentDirection;
					map->EmplaceMapObject((*node));
					(*node)->Update(deltaTime, timeTillPoisonedFall > 0.f ? settings->poisonedSpeedModifire : 1.f);
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
		Direction possibleDirection = timeTillDisorientedFall > 0.f ? OpossiteDirection(direction) : direction;
		if (possibleDirection != OpossiteDirection(nodes.front()->GetDirection()))
		{
			newDirection = possibleDirection;
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
		if (charMap[headPosition.y + static_cast<int>(directionVectorsF.at(possibleDirection).y)][headPosition.x + static_cast<int>(directionVectorsF.at(possibleDirection).x)] == 'E' ||
			charMap[headPosition.y + static_cast<int>(directionVectorsF.at(possibleDirection).y)][headPosition.x + static_cast<int>(directionVectorsF.at(possibleDirection).x)] == 'A')
		{
			nodes.front()->SetDirection(possibleDirection);
			newDirection = possibleDirection;
		}
		else
		{
			for (auto& curDir : directionVectorsF)
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
		timeTillDisorientedFall = Settings::GetSettings()->disorientationTime;
	}

	void Snake::GetPoisioned()
	{
		Settings* settings = Settings::GetSettings();
		timeTillPoisonedFall = settings->poisonedCellCount * (settings->GetTimeOnCell() / settings->poisonedSpeedModifire);
		timeTillNextCell = settings->GetTimeOnCell() / settings->poisonedSpeedModifire;
	}

	bool Snake::IsPoisioned() const
	{
		return timeTillPoisonedFall > 0.f;
	}

	bool Snake::AddNextBodyFromMap(std::vector<std::vector<bool>>& addedCells, const std::vector<std::string>& charMap, const sf::Vector2i& currentCell)
	{
		for (auto& curDir : directionVectorsI)
		{
			sf::Vector2i checkingCell = currentCell + curDir.second;

			if (map->ValidCell(checkingCell) &&
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