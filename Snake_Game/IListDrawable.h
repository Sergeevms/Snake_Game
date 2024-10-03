#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

namespace SnakeGame
{
	enum class Orientation;
	enum class Alignment;
	enum class RelativePosition;

	class IListDrawable
	{
	public:
		virtual sf::FloatRect GetRect() const = 0;
		virtual void Draw(sf::RenderWindow&, const sf::Vector2f&, const Orientation, const Alignment) = 0;
	};

	sf::FloatRect GetListRect(const std::vector<IListDrawable*> itemList, const sf::Vector2f position, const RelativePosition origin,
		const Orientation orientation, const Alignment alignment, const float spacing);

	void DrawList(sf::RenderWindow& window, const std::vector<IListDrawable*> itemList, const sf::Vector2f position,
		const RelativePosition origin, const Orientation orientation, const Alignment alignment, const float spacing);

	class ListDrawableText : public sf::Text, public IListDrawable
	{
	public:
		virtual sf::FloatRect GetRect() const override;
		virtual void Draw(sf::RenderWindow&, const sf::Vector2f&, const Orientation, const Alignment) override;
	};
}

