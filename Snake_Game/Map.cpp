#include <assert.h>
#include <fstream>

#include "Map.h"
#include "MapObject.h"
#include "Utility.h"
#include "Wall.h"
#include "Apple.h"
#include "Settings.h"

namespace SnakeGame
{
	Map::Map(const Settings& currentSettings) : settings(currentSettings)
	{
		addSpriteTexture('W', "Wall.png");
		addSpriteTexture('A', "Apple.png");
	}

	void Map::LoadFromFile(const std::string& fileName)
	{
		std::ifstream input;
		input.open(settings.levelPath + fileName);
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
					currentObject = std::make_shared<Wall>(currentCell, spritesCharToTexture['W'], settings, getWallDirection(currentCell));
					break;
				}
				case 'A':
				{
					currentObject = std::make_shared<Apple>(currentCell, spritesCharToTexture['A'], settings);
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
		map[CellToMapIndex(objectCell)] = object;
	}

	void Map::EmplaceNewApple()
	{
		sf::Vector2i newAppleCell = GetRandomEmptyCell();
		map[CellToMapIndex(newAppleCell)] = std::make_shared<Apple>(newAppleCell, spritesCharToTexture['A'], settings);
	}

	void Map::RemoveMapObject(std::shared_ptr<MapObject> object)
	{
		sf::Vector2i objectCell = object->GetCellPosition();
		map[CellToMapIndex(objectCell)] = nullptr;
	}

	void Map::RemoveMapObject(const sf::Vector2i& cell)
	{
		map[CellToMapIndex(cell)] = nullptr;
	}

	MapObjectType Map::GetObjectType(const sf::Vector2i& cell) const
	{
		if (InRightOpenInterval(0, width, cell.x) and InRightOpenInterval(0, height, cell.y))
		{
			if (map[CellToMapIndex(cell)])
			{
				return map[CellToMapIndex(cell)]->GetObjectType();
			}
			else
			{
				return MapObjectType::None;
			}
		}
		else
		{
			return MapObjectType::Wall;
		}
	}

	sf::Vector2i Map::GetRandomEmptyCell() const
	{
		sf::Vector2i checkingCell{ rand() % width, rand() % height }; 
		while (map[CellToMapIndex(checkingCell)] != nullptr)
		{
			checkingCell = { rand() % width, rand() % height };
		}
		return checkingCell;
	}

	const sf::Vector2i& Map::GetSnakeHeadPosition() const
	{
		return loadedSnakeHeadPosition;
	}

	sf::Vector2i Map::GetMapSize() const
	{
		return sf::Vector2i{ width, height };
	}

	const std::vector<std::string>& Map::GetcharMap() const
	{
		return charMap;
	}

	int Map::CellToMapIndex(const sf::Vector2i& cell) const
	{
		return cell.y * width + cell.x;
	}

	void Map::addSpriteTexture(const char type, const std::string fileName)
	{
		sf::Texture currentTexture;
		LoadTexture(settings.texturePath + fileName, currentTexture);
		spritesCharToTexture[type] = currentTexture;
	}

	Direction Map::getWallDirection(const sf::Vector2i & cell) const
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
