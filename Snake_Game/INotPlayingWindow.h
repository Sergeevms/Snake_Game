#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

namespace SnakeGame
{
	enum class RelativePosition;

	class INotPlayingWindow
	{
	public:
		virtual ~INotPlayingWindow() = default;
		virtual void Draw(sf::RenderWindow& window, const RelativePosition position) = 0;
		virtual void HandleInput(const std::vector<sf::Event>& input) = 0;
	};
}

