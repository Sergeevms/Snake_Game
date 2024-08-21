#pragma once
#include <SFML/Graphics.hpp>
#include "Settings.h"

namespace SnakeGame
{
	class DebugCell
	{
	public:
		DebugCell(Settings const& currentSettings, sf::Vector2i cell, sf::Font const& font);
		void Draw(sf::RenderWindow& window) const;
	private:
		sf::Text cellNumber;
		sf::RectangleShape rect;
	};

	class DebugGrid
	{
	public:
		DebugGrid(Settings const& currentSettings);
		void Draw(sf::RenderWindow& window) const;
		void Init(sf::Vector2i const& currentGridSize);
	private:
		Settings const& settings;
		std::vector<std::unique_ptr<DebugCell>> grid;
		sf::Font font;
	};

}
