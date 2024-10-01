#include "RecordsStateMenus.h"

namespace SnakeGame
{
	RecordsStateNameMenu::RecordsStateNameMenu() : GeneralMenu()
	{
		headerStyle.Init("Roboto-Regular.ttf", sf::Color::White, sf::Text::Style(sf::Text::Style::Bold));
		normalStyle.Init("Roboto-Regular.ttf");
		selectedStyle.Init("Roboto-Regular.ttf", sf::Color::Green);

		rootNode = InitializeNode({ nullptr }, L"������ ���", &headerStyle, MenuNodeActivateReaction::None, &subMenuStyle);
		currentNode = rootNode;

		InitializeNode(rootNode, L"���", &selectedStyle, MenuNodeActivateReaction::SkipName);
		InitializeNode(rootNode, L"��", &normalStyle, MenuNodeActivateReaction::EnterName);
	}

	RecordsStateMenu::RecordsStateMenu() : GeneralMenu()
	{
		headerStyle.Init("Roboto-Regular.ttf");
		normalStyle.Init("Roboto-Regular.ttf");
		selectedStyle.Init("Roboto-Regular.ttf", sf::Color::Green);

		rootNode = InitializeNode({ nullptr }, L"", &headerStyle, MenuNodeActivateReaction::None);
		currentNode = rootNode;

		InitializeNode(rootNode, L"������ ����", &selectedStyle, MenuNodeActivateReaction::Play);
		InitializeNode(rootNode, L"� ������� ����", &normalStyle, MenuNodeActivateReaction::MainMenu);
	}
}