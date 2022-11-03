#pragma once
#include <array>

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

enum class Texture
{
	BACKGROUND
};

enum class Font
{
	PIXELMIX
};

enum class Sound
{
	LASER
};

enum class Music
{
	MAIN_THEME
};

class Assets
{
private:
	Assets();

	std::array<sf::Texture, 1> _textures;
	std::array<sf::Font, 1> _fonts;
	std::array<sf::SoundBuffer, 0> _sounds;
	std::array<sf::Music, 0> _musics;

public:
	Assets(const Assets&) = delete;
	Assets& operator=(const Assets&) = delete;
	Assets(Assets&&) = delete;
	Assets& operator=(Assets&&) = delete;

	sf::Texture& GetTexture(Texture texture);
	sf::Font& GetFont(Font font);
	sf::SoundBuffer& GetSound(Sound sound);
	sf::Music& GetMusic(Music music);

	static auto& GetInstance() {
		static Assets instance;
		return instance;
	}
};