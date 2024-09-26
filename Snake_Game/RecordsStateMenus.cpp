#include "RecordsStateMenus.h"

namespace SnakeGame
{
	RecordsStateNameMenu::RecordsStateNameMenu(const Settings& currentSettings) : GeneralMenu(currentSettings)
	{
		headerStyle.Init("Roboto-Regular.ttf", settings, sf::Color::White, sf::Text::Style(sf::Text::Style::Bold));
		normalStyle.Init("Roboto-Regular.ttf", settings);
		selectedStyle.Init("Roboto-Regular.ttf", settings, sf::Color::Green);

		rootNode = std::make_shared<MenuNode>();
		rootNode->Init({ nullptr }, L"Ввести имя", &subMenuStyle);
		rootNode->SetStyle(&headerStyle);
		currentNode = rootNode;

		MenuNodePtr noNode = std::make_shared<MenuNode>();
		noNode->Init(rootNode, L"Нет");
		noNode->SetStyle(&selectedStyle);
		rootNode->AddChild(noNode);
		activateReactions[noNode] = ActivateReactionNameMenu::Skip;

		MenuNodePtr yesNode = std::make_shared<MenuNode>();
		yesNode->Init(rootNode, L"Да");
		yesNode->SetStyle(&normalStyle);
		rootNode->AddChild(yesNode);
		activateReactions[yesNode] = ActivateReactionNameMenu::EnterName;
	}

	ActivateReactionNameMenu RecordsStateNameMenu::GetReaction() const
	{
		return activateReactions.at(currentNode->GetCurrentlySelectedChild());
	}


	RecordsStateMenu::RecordsStateMenu(const Settings& currentSettings) : GeneralMenu(currentSettings)
	{
		headerStyle.Init("Roboto-Regular.ttf", settings);
		normalStyle.Init("Roboto-Regular.ttf", settings);
		selectedStyle.Init("Roboto-Regular.ttf", settings, sf::Color::Green);

		rootNode = std::make_shared<MenuNode>();
		rootNode->Init({ nullptr }, L"", &subMenuStyle);
		currentNode = rootNode;

		MenuNodePtr restartNode = std::make_shared<MenuNode>();
		restartNode->Init(rootNode, L"Начать игру");
		restartNode->SetStyle(&selectedStyle);
		rootNode->AddChild(restartNode);
		activateReactions[restartNode] = ActivateReactionRecordsMenu::Restart;

		MenuNodePtr mainMenuNode = std::make_shared<MenuNode>();
		mainMenuNode->Init(rootNode, L"В главное меню");
		mainMenuNode->SetStyle(&normalStyle);
		rootNode->AddChild(mainMenuNode);
		activateReactions[mainMenuNode] = ActivateReactionRecordsMenu::ToMainMenu;
	}

	ActivateReactionRecordsMenu RecordsStateMenu::GetReaction() const
	{
		return activateReactions.at(currentNode->GetCurrentlySelectedChild());
	}

}