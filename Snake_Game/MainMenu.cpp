#include "MainMenu.h"
#include "Settings.h"

namespace SnakeGame
{
	MainMenu::MainMenu(Settings& currentSettings) : GeneralMenu(currentSettings)
	{
		headerStyle.Init("Roboto-Regular.ttf", settings, sf::Color::Green, sf::Text::Style(sf::Text::Style::Bold | sf::Text::Style::Underlined), 60);
		normalStyle.Init("Roboto-Regular.ttf", settings);
		selectedStyle.Init("Roboto-Regular.ttf", settings, sf::Color::Green);

		rootNode = std::make_shared<MenuNode>();
		rootNode->Init({ nullptr }, u"Змейка", &subMenuStyle);
		rootNode->SetStyle(&headerStyle);
		currentNode = rootNode;

		MenuNodePtr playNode = std::make_shared<MenuNode>();
		playNode->Init(rootNode, u"Начать игру");
		playNode->SetStyle(&selectedStyle);
		rootNode->AddChild(playNode);
		activateReactions[playNode] = ActivateReactionMainMenu::Play;

		MenuNodePtr difficultyNode = std::make_shared<MenuNode>();
		difficultyNode->Init(rootNode, u"Уровень сложности", &subMenuStyle);
		difficultyNode->SetStyle(&normalStyle);
		rootNode->AddChild(difficultyNode);

		MenuNodePtr recordNode = std::make_shared<MenuNode>();
		recordNode->Init(rootNode, u"Таблица рекордов");
		recordNode->SetStyle(&normalStyle);
		rootNode->AddChild(recordNode);
		activateReactions[recordNode] = ActivateReactionMainMenu::Records;

		MenuNodePtr settingsNode = std::make_shared<MenuNode>();
		settingsNode->Init(rootNode, u"Настройки", &subMenuStyle);
		settingsNode->SetStyle(&normalStyle);
		rootNode->AddChild(settingsNode);

		MenuNodePtr exitNode = std::make_shared<MenuNode>();
		exitNode->Init(rootNode, u"Выход");
		exitNode->SetStyle(&normalStyle);
		rootNode->AddChild(exitNode);
		activateReactions[exitNode] = ActivateReactionMainMenu::Exit;

		std::shared_ptr<CheckBoxMenuNode> soundNode = std::make_shared<CheckBoxMenuNode>();
		soundNode->Init(settingsNode, u"Звук");
		soundNode->SetStyle(&selectedStyle);
		settingsNode->AddChild(soundNode);
		activateReactions[soundNode] = ActivateReactionMainMenu::SwitchSound;
		soundNode->setChecked(settings.soundOn);
		soundNode->setSpacing(30.f);

		std::shared_ptr<CheckBoxMenuNode> musicNode = std::make_shared<CheckBoxMenuNode>();
		musicNode->Init(settingsNode, u"Музыка");
		musicNode->SetStyle(&normalStyle);
		settingsNode->AddChild(musicNode);
		activateReactions[musicNode] = ActivateReactionMainMenu::SwitchMusic;
		musicNode->setChecked(settings.musicOn);
		musicNode->setSpacing(30.f);
		
		std::vector<std::u16string> difficultyNames{ u"Простой", u"Тяжелее простого", u"Средний", u"Легче тяжелого", u"Тяжелый" };
		for (int i = 0; i < settings.difficultyLevelCount; ++i)
		{
			std::shared_ptr<CheckBoxMenuNode> difficultySubNode = std::make_shared<CheckBoxMenuNode>();
			difficultySubNode->Init(difficultyNode, difficultyNames[i]);
			difficultySubNode->SetStyle(&normalStyle);
			difficultyNode->AddChild(difficultySubNode);
			nodeToDifficultyLevel[difficultySubNode] = i;
			activateReactions[difficultySubNode] = ActivateReactionMainMenu::SwitchDifficulty;
			difficultySubNode->setChecked(false);
			difficultySubNode->setSpacing(30.f);
		}
		difficultyNode->setSelectedChildID(settings.currentDifficulty);
		std::shared_ptr<CheckBoxMenuNode> difficultySubNode = std::dynamic_pointer_cast<CheckBoxMenuNode>(difficultyNode->GetCurrentlySelectedChild());
		difficultySubNode->SetStyle(&selectedStyle);
		difficultySubNode->setChecked(true);
	}

	ActivateReactionMainMenu MainMenu::GetReaction() const
	{
		if (activateReactions.contains(currentNode->GetCurrentlySelectedChild()))
		{
			return activateReactions.at(currentNode->GetCurrentlySelectedChild());
		}
		else
		{
			return ActivateReactionMainMenu::None;
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