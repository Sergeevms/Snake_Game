#include "PauseMenu.h"

namespace SnakeGame
{
	PauseMenu::PauseMenu() : GeneralMenu()
	{
		headerStyle.Init("Roboto-Regular.ttf", sf::Color::Green, sf::Text::Style(sf::Text::Style::Bold), 50);
		normalStyle.Init("Roboto-Regular.ttf");
		selectedStyle.Init("Roboto-Regular.ttf", sf::Color::Green);

		rootNode = InitializeNode({ nullptr }, L"�����", &headerStyle, MenuNodeActivateReaction::None, &subMenuStyle);
		currentNode = rootNode;

		InitializeNode(rootNode, L"����� �� ����", &selectedStyle, MenuNodeActivateReaction::MainMenu);
		InitializeNode(rootNode, L"����������", &normalStyle, MenuNodeActivateReaction::Play);
	}
}