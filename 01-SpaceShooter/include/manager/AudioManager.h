#pragma once
#include "Assets.h"

enum class ContinuousSoundType
{
	BURST,
	END
};

struct ContinuousSound {
	sf::Sound Sound;
	bool ShouldStop{};
	bool Active{};
};

class AudioManager final
{
private:
	AudioManager();

	sf::Music _music;
	std::vector<sf::Sound> _sounds;
	std::array<ContinuousSound, static_cast<int>(ContinuousSoundType::END)> _continuousSounds;

	Music _nextMusic;
	bool _stopMusic;

public:
	AudioManager(const AudioManager&) = delete;
	AudioManager& operator=(const AudioManager&) = delete;

	static AudioManager& GetInstance()
	{
		static AudioManager instance;
		return instance;
	}

	void Update(sf::Time elapsedTime);
	void CheckInputs(sf::Event event);

	void StartMainTheme();
	void PlayMusic(Music music);
	void StopMusic();

	void PauseAll();
	void ResumeAll();

	void PlaySound(Sound sound);

	void PlayContinuousSound(ContinuousSoundType sound);
	void StopContinuousSound(ContinuousSoundType sound);
};
