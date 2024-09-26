#include "RecordsStateInputHandlers.h"
#include "Settings.h"
#include "Game.h"
#include "RecordsStateMenus.h"
#include "RecordsState.h"

namespace SnakeGame
{
    RecordsStateNameDialogInputHandler::RecordsStateNameDialogInputHandler(Game* currentGame, Settings& currentSettings, RecordsStateNameMenu* currentMenu, RecordsState* currentState) :
        BaseInputHandler(currentGame, currentSettings), menu(currentMenu), state(currentState)
    {
		actionMapping[ActionsTypesOnInput::Up] = &RecordsStateNameDialogInputHandler::SelectPrevious;
		actionMapping[ActionsTypesOnInput::Down] = &RecordsStateNameDialogInputHandler::SelectNext;
		actionMapping[ActionsTypesOnInput::Forward] = &RecordsStateNameDialogInputHandler::ActivateCurrent;

		activateMapping[ActivateReactionNameMenu::EnterName] = &RecordsStateNameDialogInputHandler::ToNameTyping;
		activateMapping[ActivateReactionNameMenu::Skip] = &RecordsStateNameDialogInputHandler::ToRecordTable;
    }

    void RecordsStateNameDialogInputHandler::HandleInputEvents(const std::vector<sf::Event>& input)
    {
		for (auto& inputEvent : input)
		{
			if (settings.keyMap.contains(inputEvent.key.code))
			{
				if (actionMapping.contains(settings.keyMap[inputEvent.key.code]))
				{
					game->PlaySound(SoundType::OnKeyHit);
					std::invoke(actionMapping[settings.keyMap[inputEvent.key.code]], this);
				}
			}
		}

    }

	void RecordsStateNameDialogInputHandler::SelectNext()
	{
		menu->SelectNext();
	}

	void RecordsStateNameDialogInputHandler::SelectPrevious()
	{
		menu->SelectPrevious();
	}

	void RecordsStateNameDialogInputHandler::ActivateCurrent()
	{		
		std::invoke(activateMapping.at(menu->GetReaction()), this);
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
