#include "manager/AudioManager.h"
#include "Random.h"

AudioManager::AudioManager()
{
	_nextMusic = Music::END;
	_stopMusic = false;

	_continuousSounds[static_cast<int>(ContinuousSoundType::BURST)] = { sf::Sound(Assets::GetInstance().GetSound(Sound::BURST)), false, false };
}

void AudioManager::Update(const sf::Time elapsedTime)
{
	// Stop slowly the music if the next music is not END
	if (_stopMusic && _music.getStatus() != sf::SoundSource::Stopped)
	{
		const float volume = _music.getVolume() - 100.f * elapsedTime.asSeconds();

		if (volume <= 0.f)
		{
			_music.stop();
			_stopMusic = false;
			_music.setVolume(50.f);
		}
		else
		{
			_music.setVolume(volume);
		}
	}
	else if (_nextMusic != Music::END)
	{
		_music.openFromFile(Assets::GetInstance().GetMusicPath(_nextMusic));
		_music.setLoop(true);
		_music.setVolume(50.f);
		_music.play();

		_nextMusic = Music::END;
	}

	for (auto& sound : _continuousSounds)
	{
		if (sound.Active)
		{
			if (sound.ShouldStop)
			{
				const float volume = sound.Sound.getVolume() - 200.f * elapsedTime.asSeconds();

				if (volume <= 0.f)
				{
					sound.Sound.stop();
					sound.Active = false;
					sound.ShouldStop = false;
					sound.Sound.setVolume(100.f);
				}
				else
				{
					sound.Sound.setVolume(volume);
				}
			}
			else if (sound.Sound.getStatus() == sf::SoundSource::Stopped)
			{
				sound.Sound.play();
				sound.Sound.setLoop(true);
			}
		}
	}

	for (auto it = _sounds.begin(); it != _sounds.end();)
	{
		if (it->getStatus() == sf::SoundSource::Stopped)
		{
			it = _sounds.erase(it);
		}
		else
		{
			++it;
		}
	}
}

void AudioManager::StartMainTheme()
{
	const std::vector mainThemes = { Music::MAIN_THEME, Music::MAIN_THEME2 };

	_nextMusic = mainThemes[Random::GetInt(0, mainThemes.size() - 1)];
	_stopMusic = true;
}

void AudioManager::PlayMusic(const Music music)
{
	_stopMusic = true;
	_nextMusic = music;
}

void AudioManager::StopMusic()
{
	_stopMusic = true;
}

void AudioManager::PlaySound(const Sound sound)
{
	_sounds.emplace_back(sf::Sound(Assets::GetInstance().GetSound(sound)));
	_sounds.back().play();
}

void AudioManager::PlayContinuousSound(ContinuousSoundType sound)
{
	_continuousSounds[static_cast<int>(sound)].Active = true;
	_continuousSounds[static_cast<int>(sound)].ShouldStop = false;
}

void AudioManager::StopContinuousSound(ContinuousSoundType sound)
{
	_continuousSounds[static_cast<int>(sound)].ShouldStop = true;
}