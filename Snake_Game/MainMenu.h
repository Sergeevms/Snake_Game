#pragma once
#include "GeneralMenu.h"

namespace SnakeGame
{
	enum class ActivateReactionMainMenu
	{
		None, 
		Play, 
		Records,
		SwitchMusic,
		SwitchSound,
		Exit
	};

	class MainMenu : public GeneralMenu
	{
	public:
		MainMenu(Settings& currentSettings);
		virtual ~MainMenu() = default;
		ActivateReactionMainMenu GetReaction() const;
		void UpdateChecked(const bool checked);
	private:
		MenuStyle subMenuStyle;
		std::unordered_map<MenuNodePtr, ActivateReactionMainMenu> activateReactions;
	};

	class CheckBoxMenuNode : public MenuNode
	{
	public:
		CheckBoxMenuNode();
		virtual ~CheckBoxMenuNode() = default;
		void virtual Draw(sf::RenderWindow& window, const sf::Vector2f& position, const Orientation orientation, const Alignment alignment) override;
		virtual sf::FloatRect GetRect() override;
		void setChecked(const bool checked);
		virtual void SetStyle(const MenuNodeStyle* newStyle) override;
		void setSpacing(const float newSpacing);
	private:
		float spacing{ 10.f };
		bool isChecked{ false };
		sf::RectangleShape box;
		sf::CircleShape circle;
	};

}