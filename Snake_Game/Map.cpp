#include <assert.h>
#include <fstream>

#include "Map.h"
#include "MapObject.h"
#include "Utility.h"
#include "Wall.h"
#include "Apple.h"
#include "Snake.h"
#include "Settings.h"

namespace SnakeGame
{
	Map::Map()
	{
		addSpriteTexture('W', "Wall.png");
	}

	void Map::LoadFromFile(const std::string& fileName)
	{
		std::ifstream input;
		Settings* settings = Settings::GetSettings();
		input.open(settings->levelPath + fileName);
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

		emptyCellCount = width * height;
		map.reserve(width * height);

		bool applePlaced = false;

		for (int j = 0; j < height; ++j)
		{
			for (int i = 0; i < width; ++i)
			{
				sf::Vector2i currentCell{ i, j };
				std::shared_ptr<MapObject> currentObject{ nullptr };
				switch (charMap[j].at(i))
				{
				case 'W':
				{
					currentObject = std::make_shared<Wall>(currentCell, spritesCharToTexture['W'], getWallDirection(currentCell));
					break;
				}
				case 'A':
				{
					loadedApplePosition = currentCell;
					break;
				}
				case 'H':
				{
					loadedSnakeHeadPosition = currentCell;
					break;
				}
				}
				
				map.emplace_back(currentObject);
				if (currentObject && collitionResults.at(currentObject->GetObjectType()) == CollisionResult::GameOver)
				{
					--emptyCellCount;
				}
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

		if (dynamic_cast<Wall*>(object.get()) != nullptr || (dynamic_cast<SnakeNode*>(object.get()) != nullptr))
		{
			--emptyCellCount;
		}
	}

	int Map::GetEmptyCellCount() const
	{
		return emptyCellCount;
	}

	void Map::RemoveMapObject(std::shared_ptr<MapObject> object)
	{
		sf::Vector2i objectCell = object->GetCellPosition();
		RemoveMapObject(objectCell);
	}

	void Map::RemoveMapObject(const sf::Vector2i& cell)
	{
		if (map[CellToMapIndex(cell)] &&
			(dynamic_cast<Wall*>(map[CellToMapIndex(cell)].get()) != nullptr || (dynamic_cast<SnakeNode*>(map[CellToMapIndex(cell)].get()) != nullptr)))
		{
			++emptyCellCount;
		}
		map[CellToMapIndex(cell)] = nullptr;
	}

	MapObject* Map::GetObject(const sf::Vector2i& cell)
	{
		return map[CellToMapIndex(cell)].get();
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

	const sf::Vector2i& Map::GetLoadedSnakeHeadPosition() const
	{
		return loadedSnakeHeadPosition;
	}

	const sf::Vector2i& Map::GetLoadedApplePosition() const
	{
		return loadedApplePosition;
	}

	sf::Vector2i Map::GetMapSize() const
	{
		return sf::Vector2i{ width, height };
	}

	const std::vector<std::string>& Map::GetcharMap() const
	{
		return charMap;
	}

	bool Map::HaveEmptyCells() const
	{
		return emptyCellCount > 0;
	}

	bool Map::ValidCell(const sf::Vector2i& cell) const
	{
		return InRightOpenInterval(0, width, cell.x) && InRightOpenInterval(0, height, cell.y);
	}

	int Map::CellToMapIndex(const sf::Vector2i& cell) const
	{
		return cell.y * width + cell.x;
	}

	void Map::addSpriteTexture(const char type, const std::string fileName)
	{
		sf::Texture currentTexture;
		Settings* settings = Settings::GetSettings();
		LoadTexture(fileName, currentTexture);
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
