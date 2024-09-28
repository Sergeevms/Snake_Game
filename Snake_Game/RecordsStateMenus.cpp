#include "RecordsStateMenus.h"

namespace SnakeGame
{
	RecordsStateNameMenu::RecordsStateNameMenu(const Settings& currentSettings) : GeneralMenu(currentSettings)
	{
		headerStyle.Init("Roboto-Regular.ttf", settings, sf::Color::White, sf::Text::Style(sf::Text::Style::Bold));
		normalStyle.Init("Roboto-Regular.ttf", settings);
		selectedStyle.Init("Roboto-Regular.ttf", settings, sf::Color::Green);

		rootNode = InitializeNode({ nullptr }, L"������ ���", &headerStyle, MenuNodeActivateReaction::None, &subMenuStyle);
		currentNode = rootNode;

		InitializeNode(rootNode, L"���", &selectedStyle, MenuNodeActivateReaction::SkipName);
		InitializeNode(rootNode, L"��", &normalStyle, MenuNodeActivateReaction::EnterName);
	}

	RecordsStateMenu::RecordsStateMenu(const Settings& currentSettings) : GeneralMenu(currentSettings)
	{
		headerStyle.Init("Roboto-Regular.ttf", settings);
		normalStyle.Init("Roboto-Regular.ttf", settings);
		selectedStyle.Init("Roboto-Regular.ttf", settings, sf::Color::Green);

		rootNode = InitializeNode({ nullptr }, L"", &headerStyle, MenuNodeActivateReaction::None);
		currentNode = rootNode;

		InitializeNode(rootNode, L"������ ����", &selectedStyle, MenuNodeActivateReaction::Play);
		InitializeNode(rootNode, L"� ������� ����", &normalStyle, MenuNodeActivateReaction::MainMenu);
	}
}