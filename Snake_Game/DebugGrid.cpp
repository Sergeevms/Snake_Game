#include <assert.h>
#include "DebugGrid.h"
#include "Utility.h"

namespace SnakeGame
{
	DebugCell::DebugCell(Settings const& currentSettings, sf::Vector2i cell, sf::Font const& font)
	{
		cellNumber.setString(std::to_string(cell.x) + " , " + std::to_string(cell.y));
		cellNumber.setFillColor(sf::Color::Green);
		cellNumber.setFont(font);
		cellNumber.setCharacterSize(9);
		SetOriginByRelative(cellNumber, relativePositions.at(RelativePosition::Center));
		cellNumber.setPosition({ cell.x * currentSettings.tileSize + currentSettings.tileSize / 2.f, cell.y * currentSettings.tileSize + currentSettings.tileSize / 2.f });
		
		rect.setSize({ (float)currentSettings.tileSize, (float)currentSettings.tileSize });
		SetOriginByRelative(rect, relativePositions.at(RelativePosition::Center));
		rect.setPosition({ cell.x * currentSettings.tileSize + currentSettings.tileSize / 2.f, cell.y * currentSettings.tileSize + currentSettings.tileSize / 2.f });
		rect.setFillColor(sf::Color::Transparent);
		rect.setOutlineColor(sf::Color::Yellow);
		rect.setOutlineThickness(-1.f);
	}

	void DebugCell::Draw(sf::RenderWindow& window) const
	{
		window.draw(rect);
		window.draw(cellNumber);
	}

	DebugGrid::DebugGrid(Settings const& currentSettings) : settings(currentSettings)
	{
#ifdef _DEBUG
		assert(font.loadFromFile(settings.fontPath + "Roboto-Regular.ttf"));
#elif
		font.loadFromFile(settings.FONT_PATH + "Roboto-Regular.ttf");
#endif // DEBUG
	}

	void DebugGrid::Draw(sf::RenderWindow& window) const
	{
		for (auto cell = grid.begin(); cell != grid.end(); ++cell)
		{
			(*cell)->Draw(window);
		}
	}

	void DebugGrid::Init(sf::Vector2i const& currentGridSize)
	{
		grid.clear();
		for (int j = 0; j < currentGridSize.y; ++j)
		{
			for (int i = 0; i < currentGridSize.x; ++i)
			{
				grid.push_back(std::make_unique<DebugCell>(settings, sf::Vector2i{ i, j }, font));
			}
		}
	}
}