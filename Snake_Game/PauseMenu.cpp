#include "PauseMenu.h"

namespace SnakeGame
{
	PauseMenu::PauseMenu(Settings& currentSettings) : GeneralMenu(currentSettings)
	{
		headerStyle.Init("Roboto-Regular.ttf", sf::Color::Green, sf::Text::Style(sf::Text::Style::Bold), 50);
		normalStyle.Init("Roboto-Regular.ttf");
		selectedStyle.Init("Roboto-Regular.ttf", sf::Color::Green);

		rootNode = std::make_shared<MenuNode>();
		rootNode->Init({ nullptr }, u"Пауза", &subMenuStyle);
		rootNode->SetStyle(&headerStyle);
		currentNode = rootNode;

		MenuNodePtr continueNode = std::make_shared<MenuNode>();
		continueNode->Init(rootNode, u"Продолжить игру");
		continueNode->SetStyle(&selectedStyle);
		rootNode->AddChild(continueNode);
		activateReactions[continueNode] = ActivateReactionPauseMenu::Play;

		MenuNodePtr menuNode = std::make_shared<MenuNode>();
		menuNode->Init(rootNode, u"В главное меню");
		menuNode->SetStyle(&normalStyle);
		rootNode->AddChild(menuNode);
		activateReactions[menuNode] = ActivateReactionPauseMenu::MainMenu;
	}

	ActivateReactionPauseMenu PauseMenu::GetReaction() const
	{
		if (activateReactions.contains(currentNode->GetCurrentlySelectedChild()))
		{
			return activateReactions.at(currentNode->GetCurrentlySelectedChild());
		}
		else
		{
			return ActivateReactionPauseMenu::None;
		}
	}
}