#include "Snake.h"
#include "Settings.h"

namespace SnakeGame
{

	SnakeNode::SnakeNode(sf::Vector2i const& mapCell, sf::Texture const& texture, Settings const& settings, Direction direction, const float timeTillMove) :
		MapObject(mapCell, texture, settings), currentDirection(direction), timeTillMovingAvaliable(timeTillMove)
	{

	}

	void SnakeNode::Update(const float deltaTime)
	{
		if (timeTillMovingAvaliable <= 0.f)
		{
			const float movementDistance = deltaTime * currentSettings.movementSpeed;
			sf::Vector2f movement = multiplyVectorByScalar(directionVectors.at(currentDirection), movementDistance);
			screenCoordinates.x += movement.x;
			screenCoordinates.y += movement.y;
			sprite.setPosition(screenCoordinates.x, screenCoordinates.y);
		}
		else
		{
			timeTillMovingAvaliable -= deltaTime;
		}
	}

	void SnakeNode::setDirection(Direction newDirection)
	{
		currentDirection = newDirection;
	}

	Direction SnakeNode::GetDirection() const
	{
		return currentDirection;
	}

	Snake::Snake(Settings const& settings): currentSettings(settings),
		timeTillNextCell(settings.timeOnCell), newDirection(Direction::None)
	{
		loadTexture("SnakeHead.png", headTexture);
		loadTexture("SnakeBody.png", bodyTexture);
	}

	void Snake::Update(const float deltaTime)
	{
		for (auto& node : nodes)
		{
			node->Update(deltaTime);
		}
	}

	void Snake::SetNewDirection(Direction direction)
	{
		if (direction != OpossiteDirection(newDirection))
		{
			newDirection = direction;
		}
	}

	void Snake::Draw(sf::RenderWindow& window) const
	{
		for (std::shared_ptr<SnakeNode> const& node : nodes)
		{
			(*node).Draw(window);
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
		nodes.push_back(std::make_shared<SnakeNode>(currentCell, headTexture, currentSettings, Direction::None));
		while (AddNextBody(addedToSnake, charMap, currentCell))
		{
			currentCell = nodes.back()->GetCellPosition();
		}
		Direction possibleDirection = ((++nodes.begin())->get())->GetDirection();
		if (charMap[headPosition.y + (int)directionVectors.at(possibleDirection).y][headPosition.x + (int)directionVectors.at(possibleDirection).x] == 'E')
		{
			nodes.front()->setDirection(possibleDirection);
		}
		else
		{
			for (auto& curDir : directionVectors)
			{
				if (charMap[headPosition.y + (int)curDir.second.y][headPosition.x + (int)curDir.second.x] == 'E')
				{
					nodes.front()->setDirection(curDir.first);
				}
			}
		}
	}

	bool Snake::AddNextBody(std::vector<std::vector<bool>>& addedCells, std::vector<std::string> const& charMap, sf::Vector2i const& currentCell)
	{
		for (auto& curDir : directionVectors)
		{
			sf::Vector2i checkingCell{ currentCell.x + (int)curDir.second.x, currentCell.y + (int)curDir.second.y };

			if ((0 <= checkingCell.y and checkingCell.y < charMap.size()) and
				(0 <= checkingCell.x and checkingCell.x < charMap.at(checkingCell.y).size()) and
				charMap[checkingCell.y][checkingCell.x] == 'B' and
				addedCells[checkingCell.y][checkingCell.x] == false)
			{				
				nodes.push_back(std::make_shared<SnakeNode>(checkingCell, bodyTexture, currentSettings, OpossiteDirection(curDir.first)));
				addedCells[checkingCell.y][checkingCell.x] = true;
				return true;
			}
		}
		return false;
	}

	/*std::list<std::shared_ptr<SnakeNode>> const* Snake::GetNodes()
	{
		return &nodes;
	}*/

}