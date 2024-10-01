#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Utility.h"

namespace SnakeGame
{
	enum class MenuNodeActivateReaction
	{
		None,
		Play,
		Records,
		SwitchMusic,
		SwitchSound,
		SwitchDifficulty,
		Exit,
		MainMenu,
		EnterName,
		SkipName
	};

	class MenuNode;
	typedef std::shared_ptr<MenuNode> MenuNodePtr;
	typedef std::weak_ptr<MenuNode> MenuNodePtrW;
	struct Settings;

	struct MenuNodeStyle
	{
		sf::Font font;
		sf::Color color{ sf::Color::White };
		sf::Text::Style textStyle{ sf::Text::Style::Regular };
		unsigned int characterSize{ 20 };
		void Init(const std::string fontName, const sf::Color newColor = sf::Color::White, const sf::Text::Style newTextStyle = sf::Text::Style::Regular, const unsigned int newSize = 20);
	};

	struct MenuStyle
	{
		Orientation orientation{ Orientation::Vertical };
		Alignment alignment{ Alignment::Middle };
		float spacing{ 5 };
	};

	class MenuNode
	{
	public:
		virtual ~MenuNode() = default;
		virtual void Init(const MenuNodePtr parent, const std::wstring& newName, MenuStyle* newSubMenuStyle = nullptr);
		virtual void Draw(sf::RenderWindow& window, const sf::Vector2f& position, const Orientation orientation, const Alignment alignment);
		virtual sf::FloatRect GetRect();
		virtual void SetStyle(const MenuNodeStyle* newStyle);
		virtual MenuNodePtr GetCurrentlySelectedChild() const;
		MenuNodePtr GetParent() const;
		MenuStyle* GetMenuStyle() const;
		virtual void AddChild(const MenuNodePtr child);
		virtual void SelectNextChild();
		virtual void SelectPreviousChild();
		virtual std::vector<MenuNodePtr>* GetChilds();
		virtual void setSelectedChildID(int id);
	protected:
		sf::Text text;
	private:
		int selectedChildID{ -1 };
		MenuStyle* subMenuStyle{ nullptr };
		MenuNodePtrW parentNode{};
		std::vector<MenuNodePtr> childNodes;
	};	

	class GeneralMenu
	{
	public:
		GeneralMenu() {};
		virtual ~GeneralMenu() {};
		virtual void Draw(sf::RenderWindow& window, const sf::Vector2f position) const;
		virtual bool ExpandSelected();
		virtual void ReturnToPrevious();
		virtual void SelectNext() const;
		virtual void SelectPrevious() const;
		MenuNodeActivateReaction GetReaction() const;
	protected:
		MenuNodeStyle headerStyle;
		MenuNodeStyle selectedStyle;
		MenuNodeStyle normalStyle;
		std::shared_ptr<MenuNode> rootNode;
		std::shared_ptr<MenuNode> currentNode;
		std::unordered_map<MenuNodePtr, MenuNodeActivateReaction> activateReactions;
		virtual MenuNodePtr InitializeNode(const MenuNodePtr parent, const std::wstring& newName, MenuNodeStyle* nodeStyle,
			MenuNodeActivateReaction reaction, MenuStyle* newSubMenuStyle = nullptr);
		void ConfigureateNode(MenuNodePtr node, const MenuNodePtr parent, const std::wstring& newName,
			MenuNodeStyle* nodeStyle, MenuNodeActivateReaction reaction, MenuStyle* newSubMenuStyle = nullptr);
		MenuStyle subMenuStyle;
	};
}

