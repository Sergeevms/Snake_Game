#include "RecordsStateMenus.h"

namespace SnakeGame
{
	RecordsStateNameMenu::RecordsStateNameMenu() : GeneralMenu()
	{
		headerStyle.Init("Roboto-Regular.ttf", sf::Color::White, sf::Text::Style(sf::Text::Style::Bold));
		normalStyle.Init("Roboto-Regular.ttf");
		selectedStyle.Init("Roboto-Regular.ttf", sf::Color::Green);
				
		currentNode = InitializeRootNode(L"������ ���", &headerStyle, MenuNodeActivateReaction::None, &subMenuStyle);
		InitializeNode(currentNode, L"���", &selectedStyle, MenuNodeActivateReaction::SkipName);
		InitializeNode(currentNode, L"��", &normalStyle, MenuNodeActivateReaction::EnterName);
	}

	RecordsStateMenu::RecordsStateMenu() : GeneralMenu()
	{
		headerStyle.Init("Roboto-Regular.ttf");
		normalStyle.Init("Roboto-Regular.ttf");
		selectedStyle.Init("Roboto-Regular.ttf", sf::Color::Green);
		
		currentNode = InitializeRootNode(L"", &headerStyle, MenuNodeActivateReaction::None);
		InitializeNode(currentNode, L"������ ����", &selectedStyle, MenuNodeActivateReaction::Play);
		InitializeNode(currentNode, L"� ������� ����", &normalStyle, MenuNodeActivateReaction::MainMenu);
	}
}