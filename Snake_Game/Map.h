#pragma once
#include <vector>
#include <unordered_map>
#include <SFML/Graphics.hpp>

namespace SnakeGame
{
	enum class Direction;
	enum class MapObjectType;
	struct Settings;
	class MapObject;

	class Map
	{
	public:
		Map(const Settings& currentSettings);
		void LoadFromFile(const std::string& fileName);
		void CreateSavedLvl();
		void Draw(sf::RenderWindow& window) const;
		void EmplaceMapObject(std::shared_ptr <MapObject> object);
		void EmplaceNewApple();
		void RemoveMapObject(std::shared_ptr<MapObject> object);
		void RemoveMapObject(const sf::Vector2i& cell);
		MapObjectType GetObjectType(const sf::Vector2i& cell) const;
		sf::Vector2i GetRandomEmptyCell() const;
		const sf::Vector2i& GetSnakeHeadPosition() const;
		sf::Vector2i GetMapSize() const;
		const std::vector<std::string>& GetcharMap() const;
	private:
		std::vector <std::shared_ptr<MapObject>> map;
		std::unordered_map<char, sf::Texture> spritesCharToTexture;
		std::vector <std::string> charMap;
		sf::Vector2i loadedSnakeHeadPosition{ -1, -1 };
		const Settings & settings;
		int CellToMapIndex(const sf::Vector2i& cell) const;
		int width{ 0 };
		int height{ 0 };
		int applesCount{ 0 };
		int emptyCellCount{ 0 };

		void addSpriteTexture(const char type, const std::string fileName);
		Direction getWallDirection(const sf::Vector2i & cell) const;
	};
}
