#include <assert.h>
#include <string>
#include "PlayingState.h"
#include "Apple.h"
#include "Game.h"

namespace SnakeGame
{
	PlayingState::PlayingState(Game* game, Settings& settings) : BaseState(game, settings), map(settings), snake(settings, this, &map),
		inputHandler(game, settings, &snake, this), debugGrid(settings), delayBeforeMoving(settings.movingDelayOnStart)
	{		
		map.LoadFromFile(settings.selectedLevel);
		map.CreateSavedLvl();

		snake.LoadFromCharMap(map.GetcharMap(), map.GetSnakeHeadPosition());

		debugGrid.Init(map.GetMapSize());


#ifdef _DEBUG
		assert(font.loadFromFile(settings.fontPath +  "Roboto-Regular.ttf"));
#elif
		font.loadFromFile(FONT_PATH + "Roboto-Regular.ttf");
#endif // DEBUG
		gameOver.setFont(font);
		gameOver.setString("GAME OVER");
		gameOver.setFillColor(sf::Color::Red);
		gameOver.setCharacterSize(80);
		SetOriginByRelative(gameOver, relativePositions.at(RelativePosition::Center));
		gameOver.setPosition({ settings.screenWidth / 2.f, settings.screenHeight / 2.f});

		scoreText.setFont(font);
		scoreText.setFillColor(sf::Color::Green);
		scoreText.setCharacterSize(40);
		
		std::u16string currentScore(u"Очки:\n");
		scoreText.setString(sf::String::fromUtf16(currentScore.begin(), currentScore.end()) + std::to_string(scoreCount));
		SetOriginByRelative(scoreText, relativePositions.at(RelativePosition::TopRight));
		scoreText.setPosition({ settings.screenWidth - 1.f, 0.f });

		game->SwitchMusicPlaying(true);
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
			if (delayBeforeMoving <= settings.epsilon)
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
			std::u16string currentScore(u"Очки:\n");
			scoreText.setString(sf::String::fromUtf16(currentScore.begin(), currentScore.end()) + std::to_string(scoreCount));
			SetOriginByRelative(scoreText, relativePositions.at(RelativePosition::TopRight));
		}		
	}

	void PlayingState::HandleInput(std::vector<sf::Event> const& inputEvents)
	{
		inputHandler.HandleInputEvents(inputEvents);
	}

	void PlayingState::resetMovingDelay()
	{
		delayBeforeMoving = settings.movingDelayOnStart;
		sessionStarted = false;
	}

	CollisionResult PlayingState::CheckColition(sf::Vector2i& cell)
	{
		CollisionResult collitionResult = collitionResults.at(map.GetObjectType(cell));
		switch (collitionResult)
		{
		case CollisionResult::AppleEaten:
		{			
			game->PlaySound(SoundType::OnSnakeHit);
			snake.AddNewBody();
			map.EmplaceNewApple();
			scoreCount += settings.difficultyToScore[settings.currentDifficulty];
			map.RemoveMapObject(cell);
			break;
		}
		case CollisionResult::GameOver:
		{
			isGameOvered = true;
			game->PlaySound(SoundType::OnLose);
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