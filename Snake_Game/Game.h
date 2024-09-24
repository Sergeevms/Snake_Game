#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <unordered_map>

namespace SnakeGame
{
	enum class SoundType
	{
		OnKeyHit,
		OnLose,
		OnSnakeHit,
		OnSessionStart
	};

	struct Settings;
	class BaseState;
	enum class GameState;

	class Game
	{
	public:
		Game(Settings& currentSettings);
		bool IsGameShuttingDown() const;
		void Update(const float deltaTime, const std::vector<sf::Event>& inputEvents);
		void Draw(sf::RenderWindow&) const;
		void SwitchToState(GameState newState);
		void ShutDown();
		void SwitchMusicPlaying(bool playing);
		void PlaySound(const SoundType sound);

	private:
		bool isShuttingDown{ false };
		Settings& settings;
		sf::Music backGroundMusic;
		std::vector<std::shared_ptr<BaseState>> stateStack;
		std::vector<std::unique_ptr<sf::SoundBuffer>> soundBuffers;
		std::unordered_map<SoundType, sf::Sound> sounds;
		void loadSound(const SoundType type, std::string fileName);
	};
}