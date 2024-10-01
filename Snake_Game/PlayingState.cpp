#include <assert.h>
#include <string>
#include "PlayingState.h"
#include "Settings.h"
#include "Apple.h"
#include "Game.h"

namespace SnakeGame
{
	PlayingState::PlayingState() : BaseState(), map(), snake(this, &map),
		inputHandler(&snake, this), delayBeforeMoving(Settings::GetSettings()->movingDelayOnStart)
	{
		Settings* settings = Settings::GetSettings();
		map.LoadFromFile(settings->selectedLevel);
		map.CreateSavedLvl();

		snake.LoadFromCharMap(map.GetcharMap(), map.GetSnakeHeadPosition());

#ifdef _DEBUG
		assert(font.loadFromFile(settings->fontPath +  "Roboto-Regular.ttf"));
#elif
		font.loadFromFile(settings->fontPath + "Roboto-Regular.ttf");
#endif // DEBUG
		gameOver.setFont(font);
		gameOver.setString("GAME OVER");
		gameOver.setFillColor(sf::Color::Red);
		gameOver.setCharacterSize(80);
		SetOriginByRelative(gameOver, relativePositions.at(RelativePosition::Center));
		gameOver.setPosition({ settings->screenWidth / 2.f, settings->screenHeight / 2.f});

		gameWinned.setFont(font);
		gameWinned.setString("GAME WINNED");
		gameWinned.setFillColor(sf::Color::Green);
		gameWinned.setCharacterSize(80);
		SetOriginByRelative(gameWinned, relativePositions.at(RelativePosition::Center));
		gameWinned.setPosition({ settings->screenWidth / 2.f, settings->screenHeight / 2.f});


		scoreText.setFont(font);
		scoreText.setFillColor(sf::Color::Green);
		scoreText.setCharacterSize(40);
		
		std::wstring currentScore(L"Очки:\n");
		scoreText.setString(currentScore + std::to_wstring(scoreCount));
		SetOriginByRelative(scoreText, relativePositions.at(RelativePosition::TopRight));
		scoreText.setPosition({ settings->screenWidth - 1.f, 0.f });

		Game::GetGame()->SwitchMusicPlaying(true);

		keepSnakeMoveingTime = 0.f;
	}

	void PlayingState::Draw(sf::RenderWindow& window) const
	{
		map.Draw(window);
		snake.Draw(window);
		window.draw(scoreText);
		
		if (isGameOvered)
		{
			if (map.HaveEmptyCells())
			{
				window.draw(gameOver);
			}
			else
			{
				window.draw(gameWinned);
			}
		}
	}

	void PlayingState::Update(const float deltaTime)
	{
		keepSnakeMoveingTime -= deltaTime;
		Settings* settings = Settings::GetSettings();
		if (!isGameOvered)
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
				isGameOvered = true;
				game->SetLastSessionScore(scoreCount);
			}
		}
		else
		{
			if (keepSnakeMoveingTime > settings->epsilon)
			{
				snake.Update(deltaTime);				
			}
		}
	}

	void PlayingState::HandleInput(const std::vector<sf::Event>& inputEvents)
	{
		inputHandler.HandleInputEvents(inputEvents);
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