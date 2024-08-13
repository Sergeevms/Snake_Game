#include <assert.h>
#include <fstream>

#include "Map.h"
#include "Wall.h"
#include "Apple.h"
#include "Settings.h"

namespace SnakeGame
{
	Map::Map(Settings const& settings) : currentSettings{settings}
	{
		//loading sprites for MapObects
		addSpriteTexture('W', "Wall.png");
		/*addSpriteTexture('H', "SnakeHead.png");
		addSpriteTexture('B', "SnakeBody.png");*/
		addSpriteTexture('A', "Apple.png");
	}

	void Map::LoadFromFile(std::string fileName)
	{
		std::ifstream input;
		input.open(LEVEL_PATH + fileName);
		if (input.is_open())
		{
			input >> width >> height;
			charMap.clear();
			charMap.reserve(height);
			std::string currentString;
			for (int i = 0; i < height; ++i)
			{
				input >> currentString;
				charMap.push_back(currentString);
			}
			input.close();
		}
	}

	void Map::CreateSavedLvl()
	{
		if (!map.empty())
		{
			map.clear();
		}

		map.reserve(width * height);

		for (int j = 0; j < width; ++j)
		{
			for (int i = 0; i < height; ++i)
			{
				sf::Vector2i currentCell{ i, j };
				std::shared_ptr<MapObject> currentObject{ nullptr };
				switch (charMap[j].at(i))
				{
				case 'W':
				{
					currentObject = std::make_shared<Wall>(currentCell, spritesCharToTexture['W'], currentSettings, getWallDirection(currentCell));
					break;
				}
				case 'A':
				{
					currentObject = std::make_shared<Apple>(currentCell, spritesCharToTexture['A'], currentSettings);
					break;
				}
				case 'H':
				{
					loadedSnakeHeadPosition = currentCell;
					break;
				}
				}
				map.emplace_back(currentObject);
			}
		}
	}

	void Map::Draw(sf::RenderWindow& window) const
	{
		for (auto& object : map)
		{
			if (object && object->GetObjectType() != MapObjectType::Snake)
			{
				object->Draw(window);
			}
		}
	}

	void Map::EmplaceMapObject(std::shared_ptr<MapObject> object)
	{
		sf::Vector2i objectCell = object->GetCellPosition();
		map[objectCell.y * height + objectCell.x] = object;
	}

	void Map::RemoveMapObject(std::shared_ptr<MapObject> object)
	{
		sf::Vector2i objectCell = object->GetCellPosition();
		map[objectCell.y * height + objectCell.x] = nullptr;
	}

	sf::Vector2i const& Map::getSnakeHeadPosition() const
	{
		return loadedSnakeHeadPosition;
	}

	std::vector <std::string> const& Map::getcharMap() const
	{
		return charMap;
	}

	void Map::addSpriteTexture(char type, std::string fileName)
	{
		sf::Texture currentTexture;
		loadTexture(fileName, currentTexture);
		spritesCharToTexture[type] = currentTexture;
	}

	Direction Map::getWallDirection(sf::Vector2i const& cell) const
	{
		if (cell.x > 0 && charMap[cell.y].at(cell.x - 1) == 'W')
		{
			return Direction::Up;
		}
		else
		{
			if (cell.x < width - 1 && charMap[cell.y].at(cell.x + 1) == 'W')
			{
				return Direction::Down;
			}
			else
			{
				if (cell.y > 0 && charMap[cell.y - 1].at(cell.x) == 'W')
				{
					return Direction::Left;
				}
				else
				{
					return Direction::Rigth;
				}
			}
		}
	}
}
