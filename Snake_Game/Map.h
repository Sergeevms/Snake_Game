#pragma once
#include <vector>
#include <unordered_map>

#include "MapObject.h"
#include "Utility.h"

namespace SnakeGame
{
	class Map
	{
	public:
		Map(Settings const& settings);
		void LoadFromFile(std::string fileName);
		void CreateSavedLvl();
		void Draw(sf::RenderWindow& window) const;
		void EmplaceMapObject(std::shared_ptr <MapObject>);
		void RemoveMapObject(std::shared_ptr<MapObject>);
		sf::Vector2i const& getSnakeHeadPosition() const;
		std::vector <std::string> const& getcharMap() const;
	private:
		std::vector <std::shared_ptr<MapObject>> map;
		std::unordered_map<char, sf::Texture> spritesCharToTexture;
		std::vector <std::string> charMap;
		sf::Vector2i loadedSnakeHeadPosition{ -1, -1 };
		Settings const& currentSettings;
		int width{ 0 };
		int height{ 0 };
		int applesCount{ 0 };
		int emptyCellCount{ 0 };

		void addSpriteTexture(char type, std::string fileName);
		Direction getWallDirection(sf::Vector2i const& cell) const;
	};
}
