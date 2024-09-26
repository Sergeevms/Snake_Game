#pragma once
#include <vector>
#include <unordered_map>
#include <SFML/Graphics.hpp>
#include "BaseInputHandler.h"

namespace SnakeGame
{
	class Game;
	class RecordsState;
	struct Settings; 
	enum class RecordStateWindowType;

	class RecordsStateNameDialogInputHandler;
	typedef void (RecordsStateNameDialogInputHandler::* InputReaction)();
	class RecordsStateNameMenu;
	enum class ActivateReactionNameMenu;

	class RecordsStateNameDialogInputHandler : public BaseInputHandler
	{
	public:
		RecordsStateNameDialogInputHandler(Game* currentGame, Settings& currentSettings, RecordsStateNameMenu* currentMenu, RecordsState* currentState);
		void HandleInputEvents(const std::vector<sf::Event>& input) override;
	private:
		RecordsStateNameMenu* menu;
		RecordsState* state;
		std::unordered_map<ActionsTypesOnInput, InputReaction> actionMapping;
		std::unordered_map<ActivateReactionNameMenu, InputReaction> activateMapping;
		void SelectNext();
		void SelectPrevious();
		void ActivateCurrent();
		void ToNameTyping();
		void ToRecordTable();
	};
}

