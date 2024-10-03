#include "GeneralMenu.h"
#include <assert.h>
#include "Settings.h"

namespace SnakeGame
{
	void MenuNode::Init(MenuNode * parent, const std::wstring & newName, MenuStyle* newSubMenuStyle)
	{
		parentNode = parent;
		text->setString(newName);
		if (newSubMenuStyle)
		{
			subMenuStyle = newSubMenuStyle;
		}		
	}
	
	void MenuNode::Draw(sf::RenderWindow& window, const sf::Vector2f& position, const Orientation orientation, const Alignment alignment)
	{		
		text->Draw(window, position, orientation, alignment);
	}

	sf::FloatRect MenuNode::GetRect() const
	{
		return text->GetRect();
	}

	void MenuNode::SetStyle(const MenuNodeStyle* newStyle)
	{
		text->setFont(newStyle->font);
		text->setCharacterSize(newStyle->characterSize);
		text->setStyle(newStyle->textStyle);
		text->setFillColor(newStyle->color);
	}

	MenuNode* MenuNode::GetCurrentlySelectedChild() const
	{
		if (selectedChildID == -1)
		{
			return nullptr;
		}
		else
		{
			return childNodes[selectedChildID].get();
		}
	}

	MenuNode* MenuNode::GetParent() const
	{
		return parentNode;
	}

	MenuStyle* MenuNode::GetMenuStyle() const
	{
		return subMenuStyle;
	}

	void MenuNode::AddChild(std::unique_ptr<MenuNode> child)
	{
		childNodes.emplace_back(std::move(child));
		if (selectedChildID == -1)
		{
			selectedChildID = 0;
		}
	}

	void MenuNode::SelectNextChild()
	{
		if (childNodes.size() >= 1)
		{			
			selectedChildID = (selectedChildID + childNodes.size() + 1) % static_cast<int>(childNodes.size());
		}
	}

	void MenuNode::SelectPreviousChild()
	{
		if (childNodes.size() >= 1)
		{
			selectedChildID = (selectedChildID + childNodes.size() - 1) % static_cast<int>(childNodes.size());
		}
	}

	std::vector<MenuNode*> MenuNode::GetChilds()
	{
		std::vector<MenuNode*> childList;
		for (auto& child : childNodes)
		{
			childList.push_back(child.get());
		}
		return childList;
	}

	void MenuNode::setSelectedChildID(int id)
	{
		if (id >= 0 && id < childNodes.size())
		{
			selectedChildID = id;
		}
	}

	void GeneralMenu::Draw(sf::RenderWindow& window, const sf::Vector2f position) const
	{

		MenuStyle* style = currentNode->GetMenuStyle();

		std::vector<IListDrawable*> itemList;
		itemList.push_back(currentNode);

		std::vector<MenuNode*> childNodes = currentNode->GetChilds();
		for (auto& currentChild : childNodes)
		{
			itemList.push_back(currentChild);
		}
		DrawList(window, itemList, position, RelativePositionByOrientationAndAlignment(style->orientation, style->alignment), style->orientation, style->alignment, 10.f);
	}

	bool GeneralMenu::ExpandSelected()
	{		
		MenuNode* newNode = currentNode->GetCurrentlySelectedChild();
		if (newNode->GetCurrentlySelectedChild())
		{			
			currentNode = newNode;
			currentNode->SetStyle(&headerStyle);
			currentNode->GetCurrentlySelectedChild()->SetStyle(&selectedStyle);
			return true;
		}
		else
		{
			return false;
		}
	}

	void GeneralMenu::ReturnToPrevious()
	{
		MenuNode* newNode = currentNode->GetParent();
		if (newNode)
		{
			currentNode->SetStyle(&selectedStyle);
			currentNode = newNode;
			currentNode->SetStyle(&headerStyle);
		}
	}

	void GeneralMenu::SelectNext() const
	{
		currentNode->GetCurrentlySelectedChild()->SetStyle(&normalStyle);
		currentNode->SelectNextChild();
		currentNode->GetCurrentlySelectedChild()->SetStyle(&selectedStyle);
	}

	void GeneralMenu::SelectPrevious() const
	{
		currentNode->GetCurrentlySelectedChild()->SetStyle(&normalStyle);
		currentNode->SelectPreviousChild();
		currentNode->GetCurrentlySelectedChild()->SetStyle(&selectedStyle);
	}

	void MenuNodeStyle::Init(const std::string fontName, const sf::Color newColor, const sf::Text::Style newTextStyle, const unsigned int newSize)
	{
		Settings* settings = Settings::GetSettings();
#ifdef _DEBUG
		assert(font.loadFromFile(settings->fontPath + fontName));
#elif
		font.loadFromFile(settings->FONT_PATH + fontName);
#endif // DEBUG
		color = newColor;
		textStyle = newTextStyle;
		characterSize = newSize;
	}

	MenuNodeActivateReaction GeneralMenu::GetReaction() const
	{
		if (activateReactions.contains(currentNode->GetCurrentlySelectedChild()))
		{
			return activateReactions.at(currentNode->GetCurrentlySelectedChild());
		}
		else
		{
			return MenuNodeActivateReaction::None;
		}
	}

	MenuNode* GeneralMenu::InitializeRootNode(const std::wstring& newName, MenuNodeStyle* nodeStyle, MenuNodeActivateReaction reaction, MenuStyle* newSubMenuStyle)
	{
		rootNode = std::make_unique<MenuNode>();
		ConfigurateNode(rootNode.get(), nullptr, newName, nodeStyle, reaction, newSubMenuStyle);
		return rootNode.get();
	}

	MenuNode* GeneralMenu::InitializeNode(MenuNode* parent, const std::wstring& newName, MenuNodeStyle* nodeStyle, MenuNodeActivateReaction reaction, MenuStyle* newSubMenuStyle)
	{
		if (parent)
		{
			parent->AddChild(std::make_unique<MenuNode>());
			MenuNode* newNode = parent->GetChilds().back();
			ConfigurateNode(newNode, parent, newName, nodeStyle, reaction, newSubMenuStyle);
			return newNode;
		}
		else
		{
			return nullptr;
		}
	}
	void GeneralMenu::ConfigurateNode(MenuNode* node, MenuNode* parent, const std::wstring& newName,
		MenuNodeStyle* nodeStyle, MenuNodeActivateReaction reaction, MenuStyle* newSubMenuStyle)
	{
		node->Init(parent, newName, newSubMenuStyle);
		if (nodeStyle)
		{
			node->SetStyle(nodeStyle);
		}
		else
		{
			node->SetStyle(&normalStyle);
		}
		if (reaction != MenuNodeActivateReaction::None)
		{
			activateReactions[node] = reaction;
		}
	}
}
