#include "RecordsStateInputHandlers.h"
#include "Settings.h"
#include "Game.h"
#include "RecordsStateMenus.h"
#include "RecordsState.h"

namespace SnakeGame
{
    RecordsStateNameDialogInputHandler::RecordsStateNameDialogInputHandler(Game* currentGame, Settings& currentSettings, RecordsStateNameMenu* currentMenu, RecordsState* currentState) :
		BaseMenuInputHandler(currentGame, currentSettings, currentMenu), state(currentState)
    {
		activateMapping[MenuNodeActivateReaction::EnterName] = [this](BaseInputHandler* handler)
			{if (auto currentHandler = dynamic_cast<RecordsStateNameDialogInputHandler*>(this)) { currentHandler->ToNameTyping(); }};
		activateMapping[MenuNodeActivateReaction::SkipName] = [this](BaseInputHandler* handler)
			{if (auto currentHandler = dynamic_cast<RecordsStateNameDialogInputHandler*>(this)) { currentHandler->ToRecordTable(); }};
    }

	void RecordsStateNameDialogInputHandler::ToNameTyping()
	{
		state->switchToWindow(RecordStateWindowType::NameInput);
	}

	void RecordsStateNameDialogInputHandler::ToRecordTable()
	{
		state->switchToWindow(RecordStateWindowType::RecordTable);
	}
}
