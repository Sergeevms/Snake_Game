#include "PauseMenu.h"

namespace SnakeGame
{
	PauseMenu::PauseMenu(Settings& currentSettings) : GeneralMenu(currentSettings)
	{
		headerStyle.Init("Roboto-Regular.ttf", currentSettings, sf::Color::Green, sf::Text::Style(sf::Text::Style::Bold), 50);
		normalStyle.Init("Roboto-Regular.ttf", currentSettings);
		selectedStyle.Init("Roboto-Regular.ttf", currentSettings, sf::Color::Green);

		rootNode = std::make_shared<MenuNode>();
		rootNode->Init({ nullptr }, u"Пауза", &subMenuStyle);
		rootNode->SetStyle(&headerStyle);
		currentNode = rootNode;

		MenuNodePtr menuNode = std::make_shared<MenuNode>();
		menuNode->Init(rootNode, u"Выйти из игры");
		menuNode->SetStyle(&selectedStyle);
		rootNode->AddChild(menuNode);
		activateReactions[menuNode] = ActivateReactionPauseMenu::MainMenu;

		MenuNodePtr continueNode = std::make_shared<MenuNode>();
		continueNode->Init(rootNode, u"Продолжить");
		continueNode->SetStyle(&normalStyle);
		rootNode->AddChild(continueNode);
		activateReactions[continueNode] = ActivateReactionPauseMenu::Play;
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