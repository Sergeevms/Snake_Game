#include "RecordsState.h"
#include "RecordTable.h"

namespace SnakeGame
{
	RecordsState::RecordsState(Game* currentGame, Settings& currentSettings, const bool fromGame) : BaseState(currentGame, currentSettings)
	{
		table = std::make_unique<RecordTable>(currentSettings);
		table->Deserialize();
		if (fromGame)
		{

		}
	}

	void RecordsState::Draw(sf::RenderWindow&) const
	{
	}

	void RecordsState::Update(const float deltaTime)
	{
	}

	void RecordsState::HandleInput(std::vector<sf::Event> const&)
	{
	}

	void RecordsState::switchToWindow(RecordStateWindowType windowType)
	{
	}
}