#include <assert.h>
#include <string>
#include "PlayingState.h"
#include "Apple.h"

namespace SnakeGame
{
	PlayingState::PlayingState(Game* game, Settings& settings) : BaseState(game, settings), map(settings), snake(settings, this, &map),
		inputHandler(game, settings, &snake), debugGrid(settings), delayBeforeMoving(settings.movingDelayOnStart)
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

		scoreText.setFont(font);
		scoreText.setFillColor(sf::Color::Green);
		scoreText.setCharacterSize(40);
		
		std::u16string currentScore(u"Очки:\n");
		scoreText.setString(sf::String::fromUtf16(currentScore.begin(), currentScore.end()) + std::to_string(scoreCount));
		SetOriginByRelative(scoreText, relativePositions.at(RelativePosition::TopRight));
		scoreText.setPosition({ SCREEN_WIDTH - 1.f, 0.f });
	}

	void PlayingState::Draw(sf::RenderWindow& window) const
	{
		map.Draw(window);
		snake.Draw(window);
		debugGrid.Draw(window);
		window.draw(scoreText);
		if (isGameOvered)
		{
			window.draw(gameOver);
		}
	}

	void PlayingState::Update(const float deltaTime)
	{
		if (!isGameOvered)
		{
			if (delayBeforeMoving <= EPSILON)
			{
				snake.Update(deltaTime);
			}
			else
			{
				delayBeforeMoving -= deltaTime;
			}
			std::u16string currentScore(u"Очки:\n");
			scoreText.setString(sf::String::fromUtf16(currentScore.begin(), currentScore.end()) + std::to_string(scoreCount));
			SetOriginByRelative(scoreText, relativePositions.at(RelativePosition::TopRight));
		}		
	}

	void PlayingState::HandleInput(std::vector<sf::Event> const& inputEvents)
	{
		inputHandler.HandleInputEvents(inputEvents);
	}

	CollisionResult PlayingState::CheckColition(sf::Vector2i& cell)
	{
		CollisionResult collitionResult = collitionResults.at(map.GetObjectType(cell));
		switch (collitionResult)
		{
		case CollisionResult::AppleEaten:
		{			
			snake.AddNewBody();
			map.EmplaceNewApple();
			scoreCount += currentSettings.difficultyToScore[currentSettings.currentDifficulty];
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
		return collitionResult;
	}
}