#include "assert.h"
#include "Game.h"
#include "PlayingState.h"
#include "MainMenuState.h"
#include "PauseState.h"

namespace SnakeGame
{
	Game::Game(Settings& currentSettings) : settings(currentSettings)
	{		
		stateStack.push_back(std::make_shared<MainMenuState>(this, settings));
#ifdef _DEBUG
		assert(backGroundMusic.openFromFile(settings.soundPath + "Clinthammer__Background_Music.wav"));
#else// _DEBUG
		backGroundMusic.openFromFile(settings.soundPath + "Clinthammer__Background_Music.wav");
#endif
		loadSound(soundType::OnKeyHit, "Theevilsocks__menu-hover.wav");
		loadSound(soundType::OnLose, "Maodin204__Lose.wav");
		loadSound(soundType::OnSnakeHit, "Owlstorm__Snake_hit.wav");
		//loadSound(soundType::OnSessionStart, "Timgormly__Enter.aiff");
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
			stateStack.push_back(std::make_shared<MainMenuState>(this, settings));
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
				stateStack.push_back(std::make_shared<PlayingState>(this, settings));
			}
			break;
		}
		case GameState::Pause:
		{
			stateStack.push_back(std::make_shared<PauseState>(this, settings));
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
		if (playing && settings.musicOn)
		{
			backGroundMusic.play();
		}
		else
		{
			backGroundMusic.stop();
		}
	}

	void Game::PlaySound(const soundType sound)
	{
		if (sounds.contains(sound) && settings.soundOn)
		{
			sounds.at(sound).play();
		}
	}

	void Game::loadSound(const soundType type, std::string fileName)
	{
		sf::SoundBuffer newBuffer;
#ifdef _DEBUG
		assert(newBuffer.loadFromFile(settings.soundPath + fileName));
#else
		newBuffer.loadFromFile(settings.soundPath + fileName);
#endif // _DEBUG
		soundBuffers.push_back(newBuffer);
		sounds[type] = sf::Sound(soundBuffers.back());
	}
}