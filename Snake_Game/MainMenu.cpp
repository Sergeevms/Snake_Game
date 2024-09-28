#include "MainMenu.h"
#include "Settings.h"

namespace SnakeGame
{
	MainMenu::MainMenu(Settings& currentSettings) : GeneralMenu(currentSettings)
	{
		headerStyle.Init("Roboto-Regular.ttf", settings, sf::Color::Green, sf::Text::Style(sf::Text::Style::Bold | sf::Text::Style::Underlined), 60);
		normalStyle.Init("Roboto-Regular.ttf", settings);
		selectedStyle.Init("Roboto-Regular.ttf", settings, sf::Color::Green);

		rootNode = InitializeNode({ nullptr }, L"Змейка", &headerStyle, MenuNodeActivateReaction::None, &subMenuStyle);
		currentNode = rootNode;
		InitializeNode(rootNode, L"Начать игру", &selectedStyle, MenuNodeActivateReaction::Play);
		MenuNodePtr difficultyNode = InitializeNode(rootNode, L"Уровень сложности", &normalStyle, MenuNodeActivateReaction::None, &subMenuStyle);
		InitializeNode(rootNode, L"Таблица рекордов", &normalStyle, MenuNodeActivateReaction::Records);
		MenuNodePtr settingsNode = InitializeNode(rootNode, L"Настройки", &normalStyle, MenuNodeActivateReaction::None, &subMenuStyle);
		InitializeNode(rootNode, L"Выход", &normalStyle, MenuNodeActivateReaction::Exit);
		
		InitializeCheckBoxNode(settingsNode, L"Звук", settings.soundOn, 30.f, &selectedStyle, MenuNodeActivateReaction::SwitchSound);
		InitializeCheckBoxNode(settingsNode, L"Музыка", settings.musicOn, 30.f, &normalStyle, MenuNodeActivateReaction::SwitchMusic);

		std::vector<std::wstring> difficultyNames{ L"Простой", L"Тяжелее простого", L"Средний", L"Легче тяжелого", L"Тяжелый" };
		for (int i = 0; i < settings.difficultyLevelCount; ++i)
		{
			bool IsCurrentDifficultyLevel = i == settings.currentDifficulty ? true : false;
			std::shared_ptr<CheckBoxMenuNode> difficultySubNode = InitializeCheckBoxNode(difficultyNode, difficultyNames[i], IsCurrentDifficultyLevel, 30.f,
				IsCurrentDifficultyLevel ? &selectedStyle : &normalStyle, MenuNodeActivateReaction::SwitchDifficulty);
			if (IsCurrentDifficultyLevel)
			{
				difficultyNode->setSelectedChildID(i);
			}
			nodeToDifficultyLevel[difficultySubNode] = i;
		}
	}

	void MainMenu::UpdateChecked(const bool checked)
	{
		std::shared_ptr<CheckBoxMenuNode> selectedNode;
		if (selectedNode = std::dynamic_pointer_cast<CheckBoxMenuNode>(currentNode->GetCurrentlySelectedChild()))
		{
			if (nodeToDifficultyLevel.contains(selectedNode))
			{
				for (auto& node : nodeToDifficultyLevel)
				{
					std::dynamic_pointer_cast<CheckBoxMenuNode>(node.first)->setChecked(false);
				}
			}
			selectedNode->setChecked(checked);
		}
	}

	int MainMenu::GetSelectedDifficulty()
	{
		if (nodeToDifficultyLevel.contains(currentNode->GetCurrentlySelectedChild()))
		{
			return nodeToDifficultyLevel.at(currentNode->GetCurrentlySelectedChild());
		}
		else
		{
			return 0;
		}
	}

	std::shared_ptr<CheckBoxMenuNode> MainMenu::InitializeCheckBoxNode(const MenuNodePtr parent, const std::wstring& newName, bool checked, float spacing, MenuNodeStyle* nodeStyle, MenuNodeActivateReaction reaction, MenuStyle* newSubMenuStyle)
	{
		std::shared_ptr<CheckBoxMenuNode> newNode = std::make_shared<CheckBoxMenuNode>();
		ConfigureateNode(newNode, parent, newName, nodeStyle, reaction, newSubMenuStyle);
		newNode->setChecked(checked);
		newNode->setSpacing(spacing);
		return newNode;
	}

	CheckBoxMenuNode::CheckBoxMenuNode()
	{
		box.setOutlineThickness(-2.f);
		box.setFillColor({ 255, 255, 255, 0 });
	}

	void CheckBoxMenuNode::Draw(sf::RenderWindow& window, const sf::Vector2f& position, const Orientation orientation, const Alignment alignment)
	{
		sf::Vector2f origin = RelativePositionByOrientationAndAlignment(orientation, alignment);
		sf::Rect rect = GetRect();
		rect.top = position.y - rect.height * origin.y;
		rect.left = position.x - rect.width * origin.x;

		sf::Rect textRect = text.getLocalBounds();
		text.setOrigin({ textRect.left, textRect.top });
		text.setPosition({ rect.left, rect.top });
		window.draw(text);
		
		if (isChecked)
		{
			SetOriginByRelative(circle, relativePositions.at(RelativePosition::TopRight));
			circle.setPosition({ rect.left + rect.width, rect.top });
			window.draw(circle);
		}

		SetOriginByRelative(box, relativePositions.at(RelativePosition::TopRight));
		box.setPosition({ rect.left + rect.width, rect.top });
		window.draw(box);		
	}

	sf::FloatRect CheckBoxMenuNode::GetRect()
	{
		sf::FloatRect rect;
		sf::FloatRect textRect = text.getLocalBounds();
		rect.width = textRect.left + textRect.width + spacing + box.getLocalBounds().width;
		rect.height = textRect.top + textRect.height + box.getLocalBounds().height;
		return rect;
	}

	void CheckBoxMenuNode::setChecked(const bool checked)
	{
		isChecked = checked;
	}

	void CheckBoxMenuNode::SetStyle(const MenuNodeStyle* newStyle)
	{
		MenuNode::SetStyle(newStyle);
		box.setOutlineColor(newStyle->color);
		box.setSize({ static_cast<float>(newStyle->characterSize), static_cast<float>(newStyle->characterSize) });
		circle.setFillColor(newStyle->color);
		circle.setRadius(static_cast<float>(newStyle->characterSize) / 2.f);
	}
	void CheckBoxMenuNode::setSpacing(const float newSpacing)
	{
		spacing = newSpacing;
	}
}