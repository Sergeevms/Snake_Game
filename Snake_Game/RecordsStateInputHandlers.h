#pragma once
#include <vector>
#include <unordered_map>
#include <SFML/Graphics.hpp>
#include "BaseMenuInputHandler.h"

namespace SnakeGame
{
	class Game;
	class RecordsState;
	struct Settings; 
	enum class RecordStateWindowType;
	class RecordsStateNameMenu;

	class RecordsStateNameDialogInputHandler : public BaseMenuInputHandler
	{
	public:
		RecordsStateNameDialogInputHandler(RecordsStateNameMenu* currentMenu, RecordsState* currentState);
	private:
		RecordsState* state;
		void ToNameTyping();
		void ToRecordTable();
	};

	class RecordsStateTableDialogInputHandler : public BaseMenuInputHandler
	{
	public:
		RecordsStateTableDialogInputHandler(RecordsStateNameMenu* currentMenu, RecordsState* currentState);
		void RestartGame();
		void ToMainMenu();
	};

	class RecordsStateNameEnteringInputHandler : public BaseInputHandler
	{
	public:
		RecordsStateNameEnteringInputHandler(RecordsState* currentState, sf::Text& nameText);
		virtual void HandleInputEvents(const std::vector<sf::Event>& input) override;
		void ToRecordTable();
		void RemoveSymbol();
	private:
		RecordsState* state;
		sf::Text& name;
		sf::String newSymbol;
	};
}

