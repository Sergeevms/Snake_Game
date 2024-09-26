#pragma once
#include <SFML/Graphics.hpp>
#include "BaseState.h"
#include "INotPlayingWindow.h"

namespace SnakeGame
{	
	enum class RecordStateWindowType
	{
		NameDialog,
		NameInput,
		RecordTable
	};

	class RecordTable;

	class RecordsState : public BaseState
	{
	public:
		RecordsState(Game* currentGame, Settings& currentSettings, const bool fromGame);
		virtual ~RecordsState() = default;
		virtual void Draw(sf::RenderWindow& window) const override;
		virtual void Update(const float deltaTime) override;
		virtual void HandleInput(std::vector<sf::Event> const&) override;
		void switchToWindow(RecordStateWindowType windowType);
	private:
		std::unique_ptr<RecordTable> table;
		std::vector<std::unique_ptr<INotPlayingWindow>> windows;
		sf::RectangleShape background;
	};

	class RecordsStateNameMenu;
	class RecordsStateNameDialogInputHandler;

	class EnterNameDialog : public INotPlayingWindow
	{
	public:
		virtual void Draw(sf::RenderWindow& window, const RelativePosition position) override;
		virtual void HandleInput(const std::vector<sf::Event>& input) override;
	private:
		sf::RectangleShape background;
		std::unique_ptr<RecordsStateNameMenu> menu;
		std::unique_ptr<RecordsStateNameDialogInputHandler> inputHandler;
	};
}
