#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Utility.h"
#include "IListDrawable.h"

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

	class ListDrawableText;

	class MenuNode : public IListDrawable
	{
	public:
		virtual ~MenuNode() = default;
		virtual void Init(MenuNode * parent, const std::wstring& newName, MenuStyle* newSubMenuStyle = nullptr);
		virtual void Draw(sf::RenderWindow& window, const sf::Vector2f& position, const Orientation orientation, const Alignment alignment) override;
		virtual sf::FloatRect GetRect() const override;
		virtual void SetStyle(const MenuNodeStyle* newStyle);
		virtual MenuNode* GetCurrentlySelectedChild() const;
		MenuNode* GetParent() const;
		MenuStyle* GetMenuStyle() const;
		virtual void AddChild(std::unique_ptr<MenuNode> child);
		virtual void SelectNextChild();
		virtual void SelectPreviousChild();
		virtual std::vector<MenuNode*> GetChilds();
		virtual void setSelectedChildID(int id);
	protected:
		std::unique_ptr<ListDrawableText> text = std::make_unique<ListDrawableText>();
	private:
		int selectedChildID{ -1 };
		MenuStyle* subMenuStyle{ nullptr };
		MenuNode* parentNode{};
		std::vector<std::unique_ptr<MenuNode>> childNodes;
	};	

	class GeneralMenu
	{
	public:
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
		std::unique_ptr<MenuNode> rootNode;
		MenuNode* currentNode{ nullptr };
		std::unordered_map<MenuNode*, MenuNodeActivateReaction> activateReactions;
		virtual MenuNode* InitializeRootNode(const std::wstring& newName, MenuNodeStyle* nodeStyle,
			MenuNodeActivateReaction reaction, MenuStyle* newSubMenuStyle = nullptr);
		virtual MenuNode* InitializeNode(MenuNode* parent, const std::wstring& newName, MenuNodeStyle* nodeStyle,
			MenuNodeActivateReaction reaction, MenuStyle* newSubMenuStyle = nullptr);
		void ConfigurateNode(MenuNode* node, MenuNode* parent,
			const std::wstring& newName, MenuNodeStyle* nodeStyle, MenuNodeActivateReaction reaction, MenuStyle* newSubMenuStyle = nullptr);
		MenuStyle subMenuStyle;
	};
}

