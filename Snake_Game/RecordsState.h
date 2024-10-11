#pragma once
#include <SFML/Graphics.hpp>
#include "BaseState.h"
#include "NotPlayingWindow.h"
#include "IListDrawable.h"
#include "Utility.h"

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
		RecordsState(const bool fromGame);
		virtual ~RecordsState() = default;
		virtual void Draw(sf::RenderWindow& window) const override;
		virtual void HandleInput(const std::vector<sf::Event>&) override;
		void SwitchToWindow(RecordStateWindowType windowType);
	private:
		std::unique_ptr<RecordTable> table;
		std::vector<std::unique_ptr<NotPlayingWindow>> windows;
	};

	class RecordsStateNameMenu;

	class RecordsStateEnterNameDialog : public NotPlayingWindow
	{
	public:
		RecordsStateEnterNameDialog(RecordsState* state);
		virtual ~RecordsStateEnterNameDialog() = default;
		virtual void Draw(sf::RenderWindow& window) override;
	private:
		sf::RectangleShape background;
		std::unique_ptr<RecordsStateNameMenu> menu;
	};

	struct TextStyle;

	class NameEnteringWindow : public NotPlayingWindow
	{
	public:
		NameEnteringWindow(RecordsState* state);
		virtual ~NameEnteringWindow() = default;
		virtual void Draw(sf::RenderWindow& window) override;
		std::wstring GetName() const;
	private:
		sf::RectangleShape background;
		ListDrawableText name;
		ListDrawableText header;
		TextStyle textStyle;
	};

	class RecordStateMenuWindow : public NotPlayingWindow
	{
	public:
		RecordStateMenuWindow() = delete;
		RecordStateMenuWindow(RecordTable* records);
		virtual ~RecordStateMenuWindow() = default;
		virtual void Draw(sf::RenderWindow& window) override;
	private:
		RecordTable* table;
		TextStyle headerTextStyle;
		TextStyle rowTextStyle;
		ListDrawableText header;
		std::vector<ListDrawableText> textRows;
		sf::RectangleShape background;
	};

	class RecordsStateMenu;

	class RecordStateGameWindow : public NotPlayingWindow
	{
	public:
		RecordStateGameWindow(RecordTable* records, RecordsState* state);
		virtual ~RecordStateGameWindow() = default;
		virtual void Draw(sf::RenderWindow& window) override;
	private:
		RecordTable* table;
		TextStyle headerTextStyle;
		TextStyle rowTextStyle;
		std::vector<ListDrawableText> headerTexts;
		std::vector<ListDrawableText> textRows;
		sf::RectangleShape background;
		sf::RectangleShape overAllBackground;
		std::unique_ptr<RecordsStateMenu> menu;
	};
}
