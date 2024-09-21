#include "MainMenu.h"

namespace SnakeGame
{
	MainMenu::MainMenu(Settings& currentSettings) : GeneralMenu(currentSettings)
	{
		headerStyle.Init("Roboto-Regular.ttf", sf::Color::Green, sf::Text::Style(sf::Text::Style::Bold | sf::Text::Style::Underlined), 60);
		normalStyle.Init("Roboto-Regular.ttf");
		selectedStyle.Init("Roboto-Regular.ttf", sf::Color::Green);

		rootNode = std::make_shared<MenuNode>();
		rootNode->Init({ nullptr }, u"������", &subMenuStyle);
		rootNode->SetStyle(&headerStyle);
		currentNode = rootNode;

		MenuNodePtr playNode = std::make_shared<MenuNode>();
		playNode->Init(rootNode, u"������ ����");
		playNode->SetStyle(&selectedStyle);
		rootNode->AddChild(playNode);
		activateReactions[playNode] = ActivateReactionMainMenu::Play;

		MenuNodePtr difficultyNode = std::make_shared<MenuNode>();
		difficultyNode->Init(rootNode, u"������� ���������", &subMenuStyle);
		difficultyNode->SetStyle(&normalStyle);
		rootNode->AddChild(difficultyNode);

		MenuNodePtr recordNode = std::make_shared<MenuNode>();
		recordNode->Init(rootNode, u"������� ��������");
		recordNode->SetStyle(&normalStyle);
		rootNode->AddChild(recordNode);
		activateReactions[recordNode] = ActivateReactionMainMenu::Records;

		MenuNodePtr settingsNode = std::make_shared<MenuNode>();
		settingsNode->Init(rootNode, u"���������", &subMenuStyle);
		settingsNode->SetStyle(&normalStyle);
		rootNode->AddChild(settingsNode);

		MenuNodePtr exitNode = std::make_shared<MenuNode>();
		exitNode->Init(rootNode, u"�����");
		exitNode->SetStyle(&normalStyle);
		rootNode->AddChild(exitNode);
		activateReactions[exitNode] = ActivateReactionMainMenu::Exit;
	}

	ActivateReactionMainMenu MainMenu::GetReaction() const
	{
		if (activateReactions.contains(currentNode->GetCurrentlySelectedChild()))
		{
			return activateReactions.at(currentNode->GetCurrentlySelectedChild());
		}
		else
		{
			return ActivateReactionMainMenu::None;
		}
	}
}