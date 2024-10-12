#include <assert.h>
#include <string>
#include "PlayingState.h"
#include "Settings.h"
#include "Apple.h"
#include "Game.h"
#include "PlayingInputHandler.h"
#include "Snake.h"
#include "Wall.h"

namespace SnakeGame
{
	PlayingState::PlayingState() : BaseState(), map(), snake(this, &map),
		delayBeforeMoving(Settings::GetSettings()->movingDelayOnStart)
	{
		appleFactory = std::make_unique<AppleFactory>();
		inputHandler = std::make_unique<PlayingInputHandler>(&snake, this);
		Settings* settings = Settings::GetSettings();
		map.LoadFromFile(settings->selectedLevel);
		map.CreateSavedLvl();

		if (map.ValidCell(map.GetLoadedApplePosition()))
		{
			currentApple = appleFactory.get()->GenerateNewApple(&map, map.GetLoadedApplePosition());
		}
		else
		{
			currentApple = appleFactory.get()->GenerateNewApple(&map);
		}
		map.EmplaceMapObject(currentApple);

		snake.LoadFromCharMap(map.GetcharMap(), map.GetLoadedSnakeHeadPosition());

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

	bool PlayingState::CheckColition(sf::Vector2i& cell)
	{
		Game* game = Game::GetGame();
		Settings* settings = Settings::GetSettings();

		MapObject* collisionObject = map.GetObject(cell);

		if (dynamic_cast<Apple*>(collisionObject))
		{
			game->PlaySound(SoundType::OnSnakeHit);
			snake.AddNewBody();
			if (map.GetEmptyCellCount() > 1)
			{
				currentApple = appleFactory.get()->GenerateNewApple(&map);
				map.EmplaceMapObject(currentApple);
			}
			scoreCount += settings->difficultyToScore[settings->currentDifficulty];
			keepSnakeMoveingTime = settings->timeOnCell;
			if (dynamic_cast<DisorientApple*>(collisionObject))
			{
				snake.GetDisoriented();
			}
			map.RemoveMapObject(cell);
			return true;
		}
		else if (dynamic_cast<Wall*>(collisionObject) != nullptr || dynamic_cast<SnakeNode*>(collisionObject) != nullptr)
		{
			isGameOvered = true;
			game->PlaySound(SoundType::OnLose);
			game->SetLastSessionScore(scoreCount);
			game->SwitchToState(GameState::Records);
			return false;
		}
		else
		{
			return true;
		}
	}
}