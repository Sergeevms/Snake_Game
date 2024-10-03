#include "RecordsStateMenus.h"

namespace SnakeGame
{
	RecordsStateNameMenu::RecordsStateNameMenu() : GeneralMenu()
	{
		headerStyle.Init("Roboto-Regular.ttf", sf::Color::White, sf::Text::Style(sf::Text::Style::Bold));
		normalStyle.Init("Roboto-Regular.ttf");
		selectedStyle.Init("Roboto-Regular.ttf", sf::Color::Green);
				
		currentNode = InitializeRootNode(L"Ввести имя", &headerStyle, MenuNodeActivateReaction::None, &subMenuStyle);
		InitializeNode(currentNode, L"Нет", &selectedStyle, MenuNodeActivateReaction::SkipName);
		InitializeNode(currentNode, L"Да", &normalStyle, MenuNodeActivateReaction::EnterName);
	}

	RecordsStateMenu::RecordsStateMenu() : GeneralMenu()
	{
		headerStyle.Init("Roboto-Regular.ttf");
		normalStyle.Init("Roboto-Regular.ttf");
		selectedStyle.Init("Roboto-Regular.ttf", sf::Color::Green);
		
		currentNode = InitializeRootNode(L"", &headerStyle, MenuNodeActivateReaction::None);
		InitializeNode(currentNode, L"Начать игру", &selectedStyle, MenuNodeActivateReaction::Play);
		InitializeNode(currentNode, L"В главное меню", &normalStyle, MenuNodeActivateReaction::MainMenu);
	}
}