#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include "Settings.h"
#include "BaseState.h"

namespace SnakeGame
{
	enum class soundType
	{
		OnKeyHit,
		OnLose,
		OnSnakeHit,
		OnSessionStart
	};

	class Game
	{
	public:
		Game(Settings&);
		bool IsGameShuttingDown() const;
		void Update(const float deltaTime, const std::vector<sf::Event>& inputEvents);
		void Draw(sf::RenderWindow&) const;
		void SwitchToState(GameState newState);
		void ShutDown();
		void SwitchMusicPlaying(bool playing);
		void PlaySound(const soundType sound);

	private:
		bool isShuttingDown{ false };
		Settings& settings;
		sf::Music backGroundMusic;
		std::vector<std::shared_ptr<BaseState>> stateStack;
		std::vector<sf::SoundBuffer> soundBuffers;
		std::unordered_map<soundType, sf::Sound> sounds;
		void loadSound(const soundType type, std::string fileName);
	};
}