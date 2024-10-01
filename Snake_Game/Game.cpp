#include <assert.h>
#include "Game.h"
#include "Settings.h"
#include "BaseState.h"
#include "PlayingState.h"
#include "MainMenuState.h"
#include "PauseState.h"

namespace SnakeGame
{
	Game* Game::game = nullptr;

	Game::Game()
	{	
		Settings* settings = Settings::GetSettings();
		stateStack.push_back(std::make_shared<MainMenuState>());
#ifdef _DEBUG
		assert(backGroundMusic.openFromFile(settings->soundPath + "Clinthammer__Background_Music.wav"));
#else// _DEBUG
		backGroundMusic.openFromFile(settings->soundPath + "Clinthammer__Background_Music.wav");
#endif
		loadSound(SoundType::OnKeyHit, "Owlstorm__Snake_hit.wav");
		loadSound(SoundType::OnLose, "Maodin204__Lose.wav");
		loadSound(SoundType::OnSnakeHit, "Theevilsocks__menu-hover.wav");
		loadSound(SoundType::OnSessionStart, "Timgormly__Enter.wav");
	}

	bool Game::IsGameShuttingDown() const
	{
		return isShuttingDown;
	}

	void Game::Update(const float deltaTime, const std::vector<sf::Event>& inputEvents)
	{
		(*stateStack.rbegin())->HandleInput(inputEvents);
		(*stateStack.rbegin())->Update(deltaTime);
	}

	void Game::Draw(sf::RenderWindow& window) const
	{
		for (auto& state : stateStack)
		{
			state->Draw(window);
		}
	}

	void Game::SwitchToState(GameState newState)
	{
		switch (newState)
		{
		case GameState::MainMenu:
		{
			stateStack.clear();
			stateStack.push_back(std::make_shared<MainMenuState>());
			break;
		}
		case GameState::Playing:
		{
			if (std::dynamic_pointer_cast<PauseState>(stateStack.back()))
			{
				stateStack.pop_back();
			}
			else
			{
				stateStack.clear();
				stateStack.push_back(std::make_shared<PlayingState>());
			}
			break;
		}
		case GameState::Pause:
		{
			stateStack.push_back(std::make_shared<PauseState>());
			break;
		}
		}
	}

	void Game::ShutDown()
	{
		isShuttingDown = true;
	}

	void Game::SwitchMusicPlaying(bool playing)
	{
		Settings* settings = Settings::GetSettings();
		if (playing && settings->musicOn)
		{
			backGroundMusic.play();
		}
		else
		{
			backGroundMusic.stop();
		}
	}

	void Game::PlaySound(const SoundType sound)
	{
		Settings* settings = Settings::GetSettings();
		if (sounds.contains(sound) && settings->soundOn)
		{
			sounds.at(sound).play();
		}
	}

	void Game::SetLastSessionScore(const int score)
	{
		lastSessionScore = score;
	}

	int Game::GetLastSessionScore()
	{
		return lastSessionScore;
	}

	void Game::loadSound(const SoundType type, std::string fileName)
	{
		Settings* settings = Settings::GetSettings();
		soundBuffers.push_back(std::make_unique<sf::SoundBuffer>());
#ifdef _DEBUG
		assert((*soundBuffers.back()).loadFromFile(settings->soundPath + fileName));
#else
		newBuffer.loadFromFile(settings->soundPath + fileName);
#endif // _DEBUG
		sounds[type] = sf::Sound(*soundBuffers.back());
	}
}