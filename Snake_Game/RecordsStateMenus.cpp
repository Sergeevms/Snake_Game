#include "RecordsStateMenus.h"

namespace SnakeGame
{
	RecordsStateNameMenu::RecordsStateNameMenu(const Settings& currentSettings) : GeneralMenu(currentSettings)
	{
		headerStyle.Init("Roboto-Regular.ttf", settings, sf::Color::White, sf::Text::Style(sf::Text::Style::Bold));
		normalStyle.Init("Roboto-Regular.ttf", settings);
		selectedStyle.Init("Roboto-Regular.ttf", settings, sf::Color::Green);

		rootNode = InitializeNode({ nullptr }, L"Ввести имя", &headerStyle, MenuNodeActivateReaction::None, &subMenuStyle);
		currentNode = rootNode;

		InitializeNode(rootNode, L"Нет", &selectedStyle, MenuNodeActivateReaction::SkipName);
		InitializeNode(rootNode, L"Да", &normalStyle, MenuNodeActivateReaction::EnterName);
	}

	RecordsStateMenu::RecordsStateMenu(const Settings& currentSettings) : GeneralMenu(currentSettings)
	{
		headerStyle.Init("Roboto-Regular.ttf", settings);
		normalStyle.Init("Roboto-Regular.ttf", settings);
		selectedStyle.Init("Roboto-Regular.ttf", settings, sf::Color::Green);

		rootNode = InitializeNode({ nullptr }, L"", &headerStyle, MenuNodeActivateReaction::None);
		currentNode = rootNode;

		InitializeNode(rootNode, L"Начать игру", &selectedStyle, MenuNodeActivateReaction::Play);
		InitializeNode(rootNode, L"В главное меню", &normalStyle, MenuNodeActivateReaction::MainMenu);
	}
}