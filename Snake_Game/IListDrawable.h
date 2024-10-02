#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

namespace SnakeGame
{
	enum class Orientation;
	enum class Alignment;

	class IListDrawable
	{
	public:
		virtual sf::FloatRect GetRect() = 0;
		virtual void Draw(sf::RenderWindow&, const sf::Vector2f, Orientation, Alignment) = 0;
	};

	sf::FloatRect GetListRect(const std::vector<IListDrawable*> itemList, const sf::Vector2f position, const RelativePosition origin,
		const Orientation orientation, const Alignment alignment, const float spacing);

	void DrawList(sf::RenderWindow window, const std::vector<IListDrawable*> itemList, const sf::Vector2f position,
		const RelativePosition origin, const Orientation orientation, const Alignment alignment, const float spacing);
}

