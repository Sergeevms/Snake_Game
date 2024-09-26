#include "GeneralMenu.h"
#include <assert.h>
#include "Settings.h"

namespace SnakeGame
{
	void MenuNode::Init(const MenuNodePtr parent, const std::wstring & newName, MenuStyle* newSubMenuStyle)
	{
		parentNode = parent;
		subMenuStyle = newSubMenuStyle;
		text.setString(newName);
	}
	
	void MenuNode::Draw(sf::RenderWindow& window, const sf::Vector2f& position, const Orientation orientation, const Alignment alignment)
	{		
		SetOriginByRelative(text, RelativePositionByOrientationAndAlignment(orientation, alignment));
		text.setPosition(position);
		window.draw(text);
	}

	sf::FloatRect MenuNode::GetRect()
	{
		return text.getLocalBounds();
	}

	void MenuNode::SetStyle(const MenuNodeStyle* newStyle)
	{
		text.setFont(newStyle->font);
		text.setCharacterSize(newStyle->characterSize);
		text.setStyle(newStyle->textStyle);
		text.setFillColor(newStyle->color);
	}

	MenuNodePtr MenuNode::GetCurrentlySelectedChild() const
	{
		if (selectedChildID == -1)
		{
			return MenuNodePtr(nullptr);
		}
		else
		{
			return childNodes[selectedChildID];
		}
	}

	MenuNodePtr MenuNode::GetParent() const
	{
		return parentNode.lock();
	}

	MenuStyle* MenuNode::GetMenuStyle() const
	{
		return subMenuStyle;
	}

	void MenuNode::AddChild(const MenuNodePtr child)
	{
		childNodes.push_back(child);
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

	std::vector<MenuNodePtr>* MenuNode::GetChilds()
	{
		return &childNodes;
	}

	void MenuNode::setSelectedChildID(int id)
	{
		if (id >= 0 && id < childNodes.size())
		{
			selectedChildID = id;
		}
	}

	GeneralMenu::GeneralMenu(const Settings& currentSettings) : settings(currentSettings)
	{
		
	}

	void GeneralMenu::Draw(sf::RenderWindow& window, const sf::Vector2f position) const
	{

		MenuStyle* style = currentNode->GetMenuStyle();

		sf::FloatRect totalRect;
		sf::FloatRect currentRect = currentNode->GetRect();

		float maxNodeSize = 0;

		std::vector<MenuNodePtr>* childNodes = currentNode->GetChilds();

		for (auto& currentChild : *childNodes)
		{
			currentRect = currentChild->GetRect();
			if (style->orientation == Orientation::Vertical)
			{
				totalRect.width = std::max(totalRect.width, currentRect.width + currentRect.left);
				maxNodeSize = std::max(maxNodeSize, currentRect.height + currentRect.top);
			}
			else
			{
				totalRect.height = std::max(totalRect.height, currentRect.height + currentRect.top);
				maxNodeSize = std::max(maxNodeSize, currentRect.width + currentRect.left);
			}
		}

		if (style->orientation == Orientation::Vertical)
		{
			totalRect.height = maxNodeSize * childNodes->size() + (style->spacing * childNodes->size() - 1);
		}
		else
		{
			totalRect.width = maxNodeSize * childNodes->size() + (style->spacing * childNodes->size() - 1);
		}

		currentNode->Draw(window, position, style->orientation, style->alignment);

		sf::Vector2f relativeOrigin = RelativePositionByOrientationAndAlignment(style->orientation, style->alignment);
		currentRect = currentNode->GetRect();
		totalRect.left = position.x - totalRect.width * relativeOrigin.x + 
			(style->orientation == Orientation::Vertical ? 0.f : currentRect.width + currentRect.left + style->spacing * 2.f);
		totalRect.top = position.y - totalRect.height * relativeOrigin.y +
			(style->orientation == Orientation::Vertical ? currentRect.height + currentRect.top + style->spacing * 2.f : 0.f);

		sf::Vector2f currentPosition;
		currentPosition.x = totalRect.left + (style->orientation == Orientation::Vertical ? totalRect.width * relativeOrigin.x : 0.f);
		currentPosition.y = totalRect.top + (style->orientation == Orientation::Vertical ? 0.f : totalRect.height * relativeOrigin.y);		

		for (auto &currentChild : *childNodes)
		{
			currentRect = currentChild->GetRect();
			currentChild->Draw(window, currentPosition, style->orientation, style->alignment);
			if (style->orientation == Orientation::Vertical)
			{
				currentPosition.y += currentRect.height + style->spacing;
			}
			else
			{
				currentPosition.x += currentRect.width + style->spacing;
			}
		}
	}

	bool GeneralMenu::ExpandSelected()
	{		
		MenuNodePtr newNode = currentNode->GetCurrentlySelectedChild();
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
		MenuNodePtr newNode = currentNode->GetParent();
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

	void MenuNodeStyle::Init(const std::string fontName, const Settings& settings, const sf::Color newColor, const sf::Text::Style newTextStyle, const unsigned int newSize)
	{
#ifdef _DEBUG
		assert(font.loadFromFile(settings.fontPath + fontName));
#elif
		font.loadFromFile(settings.FONT_PATH + fontName);
#endif // DEBUG
		color = newColor;
		textStyle = newTextStyle;
		characterSize = newSize;
	}
}
