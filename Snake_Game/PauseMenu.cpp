#include "PauseMenu.h"

namespace SnakeGame
{
	PauseMenu::PauseMenu(const Settings& currentSettings) : GeneralMenu(currentSettings)
	{
		headerStyle.Init("Roboto-Regular.ttf", currentSettings, sf::Color::Green, sf::Text::Style(sf::Text::Style::Bold), 50);
		normalStyle.Init("Roboto-Regular.ttf", currentSettings);
		selectedStyle.Init("Roboto-Regular.ttf", currentSettings, sf::Color::Green);

		rootNode = InitializeNode({ nullptr }, L"Пауза", &headerStyle, MenuNodeActivateReaction::None, &subMenuStyle);
		currentNode = rootNode;

		InitializeNode(rootNode, L"Выйти из игры", &selectedStyle, MenuNodeActivateReaction::MainMenu);
		InitializeNode(rootNode, L"Продолжить", &normalStyle, MenuNodeActivateReaction::Play);
	}
}