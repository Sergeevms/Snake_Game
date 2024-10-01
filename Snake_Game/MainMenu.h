#pragma once
#include "GeneralMenu.h"

namespace SnakeGame
{
	class CheckBoxMenuNode;

	class MainMenu : public GeneralMenu
	{
	public:
		MainMenu();
		virtual ~MainMenu() = default;
		void UpdateChecked(const bool checked);
		int GetSelectedDifficulty();
	private:
		std::shared_ptr<CheckBoxMenuNode> InitializeCheckBoxNode(const MenuNodePtr parent, const std::wstring& newName, bool checked, float spacing, MenuNodeStyle* nodeStyle = nullptr,
			MenuNodeActivateReaction reaction = MenuNodeActivateReaction::None, MenuStyle* newSubMenuStyle = nullptr);
		std::unordered_map<MenuNodePtr, int> nodeToDifficultyLevel;
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