#include "RecordsStateMenus.h"

namespace SnakeGame
{
	RecordsStateNameMenu::RecordsStateNameMenu() : GeneralMenu()
	{
		headerStyle.Init("Roboto-Regular.ttf", sf::Color::White, sf::Text::Style(sf::Text::Style::Bold));
		normalStyle.Init("Roboto-Regular.ttf");
		selectedStyle.Init("Roboto-Regular.ttf", sf::Color::Green);

		rootNode = InitializeNode({ nullptr }, L"Ввести имя", &headerStyle, MenuNodeActivateReaction::None, &subMenuStyle);
		currentNode = rootNode;

		InitializeNode(rootNode, L"Нет", &selectedStyle, MenuNodeActivateReaction::SkipName);
		InitializeNode(rootNode, L"Да", &normalStyle, MenuNodeActivateReaction::EnterName);
	}

	RecordsStateMenu::RecordsStateMenu() : GeneralMenu()
	{
		headerStyle.Init("Roboto-Regular.ttf");
		normalStyle.Init("Roboto-Regular.ttf");
		selectedStyle.Init("Roboto-Regular.ttf", sf::Color::Green);

		rootNode = InitializeNode({ nullptr }, L"", &headerStyle, MenuNodeActivateReaction::None);
		currentNode = rootNode;

		InitializeNode(rootNode, L"Начать игру", &selectedStyle, MenuNodeActivateReaction::Play);
		InitializeNode(rootNode, L"В главное меню", &normalStyle, MenuNodeActivateReaction::MainMenu);
	}
}