#include <assert.h>
#include "PlayingState.h"
#include "Apple.h"

namespace SnakeGame
{
	PlayingState::PlayingState(Game* game, Settings& settings) : BaseState(game, settings), map(settings), snake(settings, this, &map), inputHandler(game, settings, &snake), debugGrid(settings)
	{		
		map.LoadFromFile(settings.selectedLevel);
		map.CreateSavedLvl();

		snake.LoadFromCharMap(map.GetcharMap(), map.GetSnakeHeadPosition());

		debugGrid.Init(map.GetMapSize());


#ifdef _DEBUG
		assert(font.loadFromFile(RESOURCES_PATH + "Fonts/Roboto-Regular.ttf"));
#elif
		font.loadFromFile(RESOURCES_PATH + "Fonts/Roboto-Regular.ttf");
#endif // DEBUG
		gameOver.setFont(font);
		gameOver.setString("GAME OVER");
		gameOver.setFillColor(sf::Color::Red);
		gameOver.setCharacterSize(80);
		SetOriginByRelative(gameOver, relativePositions.at(RelativePosition::Center));
		gameOver.setPosition({SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f});
	}

	void PlayingState::Draw(sf::RenderWindow& window) const
	{
		map.Draw(window);
		snake.Draw(window);
		//debugGrid.Draw(window);
		if (isGameOvered)
		{
			window.draw(gameOver);
		}
	}

	void PlayingState::Update(const float deltaTime)
	{
		if (!isGameOvered)
		{
			snake.Update(deltaTime);
		}
	}

	void PlayingState::HandleInput(std::vector<sf::Event> const& inputEvents)
	{
		inputHandler.HandleInputEvents(inputEvents);
	}

	void PlayingState::CheckColition(sf::Vector2i& cell)
	{
		CollisionResult collitionResult = collitionResults.at(map.GetObjectType(cell));
		switch (collitionResult)
		{
		case CollisionResult::AppleEaten:
		{			
			snake.AddNewBody();
			map.EmplaceNewApple();
			map.RemoveMapObject(cell);
			break;
		}
		case CollisionResult::GameOver:
		{
			isGameOvered = true;
			break;
		}
		case CollisionResult::None:
		{

		}
		}
	}
}