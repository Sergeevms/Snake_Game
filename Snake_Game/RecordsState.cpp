#include "RecordsState.h"
#include "RecordTable.h"
#include "RecordsStateInputHandlers.h"

namespace SnakeGame
{
	RecordsState::RecordsState(const bool fromGame) : BaseState()
	{
		table = std::make_unique<RecordTable>();
		table->Deserialize();
		if (fromGame)
		{

		}
	}

	void RecordsState::Draw(sf::RenderWindow& window) const
	{
	}

	void RecordsState::Update(const float deltaTime)
	{
	}

	void RecordsState::HandleInput(std::vector<sf::Event> const& input)
	{
	}

	void RecordsState::SwitchToWindow(RecordStateWindowType windowType)
	{
	}

	void EnterNameDialog::Draw(sf::RenderWindow& window, const RelativePosition position)
	{
	}

	void EnterNameDialog::HandleInput(const std::vector<sf::Event>& input)
	{
		inputHandler->HandleInputEvents(input);
	}

	void NameEnteringWindow::Draw(sf::RenderWindow& window, const RelativePosition position)
	{
	}

	void NameEnteringWindow::HandleInput(const std::vector<sf::Event>& input)
	{
		inputHandler->HandleInputEvents(input);
	}
}