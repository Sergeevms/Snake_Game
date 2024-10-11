#include <assert.h>
#include <string>
#include "PlayingState.h"
#include "Settings.h"
#include "Apple.h"
#include "Game.h"
#include "PlayingInputHandler.h"

namespace SnakeGame
{
	PlayingState::PlayingState() : BaseState(), map(), snake(this, &map),
		delayBeforeMoving(Settings::GetSettings()->movingDelayOnStart)
	{
		inputHandler = std::make_unique<PlayingInputHandler>(&snake, this);
		Settings* settings = Settings::GetSettings();
		map.LoadFromFile(settings->selectedLevel);
		map.CreateSavedLvl();

		snake.LoadFromCharMap(map.GetcharMap(), map.GetSnakeHeadPosition());

#ifdef _DEBUG
		assert(font.loadFromFile(settings->fontPath +  "Roboto-Regular.ttf"));
#elif
		font.loadFromFile(settings->fontPath + "Roboto-Regular.ttf");
#endif // DEBUG

		scoreText.setFont(font);
		scoreText.setFillColor(sf::Color::Green);
		scoreText.setCharacterSize(40);
		
		std::wstring currentScore(L"Очки:\n");
		scoreText.setString(currentScore + std::to_wstring(scoreCount));
		SetOriginByRelative(scoreText, relativePositions.at(RelativePosition::TopRight));
		scoreText.setPosition({ settings->screenWidth - 10.f, 5.f });

		Game::GetGame()->SwitchMusicPlaying(true);

		keepSnakeMoveingTime = 0.f;
	}

	void PlayingState::Draw(sf::RenderWindow& window) const
	{
		map.Draw(window);
		snake.Draw(window);
		window.draw(scoreText);
	}

	void PlayingState::Update(const float deltaTime)
	{
		keepSnakeMoveingTime -= deltaTime;
		Settings* settings = Settings::GetSettings();
		if (isGameOvered)
		{
			if (keepSnakeMoveingTime > settings->epsilon)
			{
				snake.Update(deltaTime);
			}
		}
		else
		{
			Game* game = Game::GetGame();
			if (delayBeforeMoving <= settings->epsilon)
			{
				snake.Update(deltaTime);
				if (!sessionStarted)
				{
					sessionStarted = true;
					game->PlaySound(SoundType::OnSessionStart);
				}
			}
			else
			{
				delayBeforeMoving -= deltaTime;
			}
			std::wstring currentScore(L"Очки:\n");
			scoreText.setString(currentScore + std::to_wstring(scoreCount));
			SetOriginByRelative(scoreText, relativePositions.at(RelativePosition::TopRight));
			if (!map.HaveEmptyCells())
			{
				game->SetLastSessionScore(scoreCount);
				game->SwitchToState(GameState::Records);
				isGameOvered = true;
			}
		}
	}

	void PlayingState::resetMovingDelay()
	{
		delayBeforeMoving = Settings::GetSettings()->movingDelayOnStart;
		sessionStarted = false;
	}

	CollisionResult PlayingState::CheckColition(sf::Vector2i& cell)
	{
		CollisionResult collitionResult = collitionResults.at(map.GetObjectType(cell));
		Game* game = Game::GetGame();
		Settings* settings = Settings::GetSettings();

		switch (collitionResult)
		{
		case CollisionResult::AppleEaten:
		{			
			game->PlaySound(SoundType::OnSnakeHit);
			snake.AddNewBody();
			map.EmplaceNewApple();
			scoreCount += settings->difficultyToScore[settings->currentDifficulty];
			keepSnakeMoveingTime = settings->timeOnCell;
			map.RemoveMapObject(cell);
			break;
		}
		case CollisionResult::GameOver:
		{
			isGameOvered = true;
			game->PlaySound(SoundType::OnLose);
			game->SetLastSessionScore(scoreCount);
			game->SwitchToState(GameState::Records);
			break;
		}
		case CollisionResult::None:
		{
			break;
		}
		}
		return collitionResult;
	}
}