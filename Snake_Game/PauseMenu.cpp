#include "PauseMenu.h"

namespace SnakeGame
{
	PauseMenu::PauseMenu() : GeneralMenu()
	{
		headerStyle.Init("Roboto-Regular.ttf", sf::Color::Green, sf::Text::Style(sf::Text::Style::Bold), 50);
		normalStyle.Init("Roboto-Regular.ttf");
		selectedStyle.Init("Roboto-Regular.ttf", sf::Color::Green);
		
		currentNode = InitializeRootNode(L"�����", &headerStyle, MenuNodeActivateReaction::None, &subMenuStyle);
		InitializeNode(currentNode, L"����� �� ����", &selectedStyle, MenuNodeActivateReaction::MainMenu);
		InitializeNode(currentNode, L"����������", &normalStyle, MenuNodeActivateReaction::Play);
	}
}