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
		RecordsStateNameDialogInputHandler(Game* currentGame, Settings& currentSettings, RecordsStateNameMenu* currentMenu, RecordsState* currentState);
	private:
		RecordsState* state;
		void ToNameTyping();
		void ToRecordTable();
	};
}

